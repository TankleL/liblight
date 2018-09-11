/*******************************************************************************
@module rennderer-patht

@abbreviation patht ==> path tracing

@link path tracing reference - https://en.wikipedia.org/wiki/Path_tracing

==----------------------------------------------------------------------------==

MIT License

Copyright (c) 2018 Tankle L.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

#include "api-dev-mod.hpp"
#include "../tools/math/inc/mathinc.h"
#include "../inc/renderer-patht.hpp"
#include "../inc/material-default.hpp"

using namespace Light;
using namespace Light::Math;

RdrrPathTracing::RdrrPathTracing(int sample_scale,
	int max_radiance_depth)
	: m_sample_scale(sample_scale)
	, m_max_radiance_depth(max_radiance_depth)
{}

void RdrrPathTracing::set_camera(std::shared_ptr<Camera> camera)
{
	m_camera = camera;
}

void RdrrPathTracing::render(Texture2D& output, const Scene& scene)
{
	const decimal rw = (decimal)output.get_resolution().get_width();
	const decimal rh = (decimal)output.get_resolution().get_height();
	const decimal h_rw = rw * 0.5;
	const decimal h_rh = rh * 0.5;

	Ray3 cray(Point3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f));
	for (decimal y = 0; y < rh; y += 1.0)
	{
		printf("\rrendering, current row = %d, progress = %3.2f%%", (int)y, y / rh * 100.0);
		for (decimal x = 0; x < rw; x += 1.0)
		{
			Color pixel;
			int hit_count = 0;

			Color c_shade;
			for (int s = 0; s < m_sample_scale; ++s)
			{
				const decimal px = (x - h_rw + DecimalRandom::dice() - 0.5) / rw;
				const decimal py = (y - h_rh + DecimalRandom::dice() - 0.5) / rh;

				m_camera->generate_ray(cray, px, py);
				Color s_shade;
				if (_radiance(s_shade, scene, cray, 0))
				{
					++hit_count;
					pixel += s_shade / (decimal)m_sample_scale;
				}
			}

			if (hit_count)
			{
				pixel.clamp();
				output.set_pixel((int)x, (int)y, pixel);
			}
		}
	}
}

bool RdrrPathTracing::_radiance(Math::Color& output, const Scene& scene, const Math::Ray3& ray_in, int depth)
{
	bool retval = false;
	bool quit = false;
	
	Scene::HitInfo hit_info;
	quit = !scene.hit_detect(hit_info, ray_in);

	if (!quit)
	{	
		if (depth > m_max_radiance_depth)
		{ // Russian Roulette
			// Stop the recursion randomly based on the surface reflectivity.
			// TODO: impl R.R.
			return false;
		}
		else
		{
			++depth;

			retval = true;
			if ("default" == hit_info.mtrl->type())
			{
				const DefaultMaterial* mtrl = 
					static_cast<const DefaultMaterial*>(hit_info.mtrl);

				const Point3& x = hit_info.inters.m_hit_point;
				const Vector3& n = hit_info.inters.m_normal;
				const Ray3& r = ray_in;

				Vector3 nl = n.dot(r.m_direction) < 0 ?	n : n * -1;

				if (mtrl->has_property(DefaultMaterial::DIFFUSE))
				{
					Color diff;

					if (_radiance(diff, scene, _random_ray(nl, x), depth))
					{
						output += mtrl->get_color(DefaultMaterial::DIFFUSE) * diff;
					}
				}

				if (mtrl->has_property(DefaultMaterial::SPECULAR))
				{
					Color spec;
					Ray3 ray_rfl = _reflect_ray(ray_in, x, n);

					if (_radiance(spec, scene, ray_rfl, depth))
					{
						output += mtrl->get_color(DefaultMaterial::SPECULAR) * spec;
					}
				}

				if (mtrl->has_property(DefaultMaterial::REFRACT))
				{
					Ray3 ref_ray(x, r.m_direction - n*2*n.dot(r.m_direction));
					bool is_going_in = n.dot(nl) > 0.0;
					decimal nc = 1.0;
					decimal nt = 1.5;
					decimal nnt = is_going_in ? nc / nt : nt / nc, ddn = r.m_direction.dot(nl);
					decimal cos2t = 1 - nnt * nnt*(1 - ddn * ddn);

					if (cos2t < 0) // // Total internal reflection
					{
						Color refr;
						if (_radiance(refr, scene, ref_ray, depth))
						{
							output += mtrl->get_color(DefaultMaterial::REFRACT) * refr;
						}
					}
					else
					{
						Vector3 tdir = (r.m_direction*nnt - n * ((is_going_in ? 1 : -1)*(ddn*nnt + sqrt(cos2t))));
						tdir.normalize();

						double a = nt - nc, b = nt + nc, R0 = a * a / (b*b), c = 1 - (is_going_in ? -ddn : tdir.dot(n));
						double Re = R0 + (1 - R0)*c*c*c*c*c, Tr = 1 - Re, P = .25 + .5*Re, RP = Re / P, TP = Tr / (1 - P);

						Color refr;
						if (depth > 2)
						{
							// Russian roulette 
							if (DecimalRandom::dice() < P)
							{
								if (_radiance(refr, scene, ref_ray, depth))
								{
									output += mtrl->get_color(DefaultMaterial::REFRACT) * refr * RP;
								}
							}
							else
							{
								if (_radiance(refr, scene, Ray3(x, tdir), depth))
								{
									output += mtrl->get_color(DefaultMaterial::REFRACT) * refr * TP;
								}
							}
						}
						else
						{
							if (_radiance(refr, scene, ref_ray, depth))
							{
								output += mtrl->get_color(DefaultMaterial::REFRACT) * refr * Re;
							}

							if (_radiance(refr, scene, Ray3(x, tdir), depth))
							{
								output += mtrl->get_color(DefaultMaterial::REFRACT) * refr * TP;
							}
						}
					}
				}

				if (mtrl->has_property(DefaultMaterial::EMISSIVE))
				{
					output += mtrl->get_color(DefaultMaterial::EMISSIVE);
				}
			}
		}
	}

	return retval;
}

Math::Ray3 RdrrPathTracing::_random_ray(const Math::Vector3& normal, const Math::Point3& hit_pos) const
{
	const decimal ra = d_pi * DecimalRandom::dice();
	const decimal rb = DecimalRandom::dice();
	const decimal rb_sqrt = sqrt(rb);
	
	const Vector3& w = normal;
	Vector3 u = (abs(normal.m_x) > 0.1 ? Vector3(0, 1, 0) : Vector3(1, 0, 0)).cross(w);
	u.normalize();
	Vector3 v = w.cross(u);
	Vector3 dir = u * cos(ra)*rb_sqrt + v * sin(ra)*rb_sqrt + w * sqrt(1 - rb);
	dir.normalize();
	return Ray3(hit_pos, dir);
}

Math::Ray3 RdrrPathTracing::_reflect_ray(const Math::Ray3& ray_in, const Math::Point3& hit_point, const Math::Vector3& normal) const
{
	return Ray3(hit_point, ray_in.m_direction - normal * 2 * normal.dot(ray_in.m_direction));
}