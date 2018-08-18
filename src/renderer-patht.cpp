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
	int msaa_scale,
	int max_radiance_depth)
	: m_sample_scale(sample_scale)
	, m_msaa_scale(msaa_scale)
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

	const int msaa_count = m_msaa_scale * m_msaa_scale;
	Ray3 cray(Point3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f));
	Color pixel;
	bool hit(false);
	for (decimal y = 0; y < rh; y += 1.0)
	{
		for (decimal x = 0; x < rw; x += 1.0)
		{
			pixel = 0.0;
			hit = false;
			for (int msaa = 0; msaa < msaa_count; ++msaa)
			{
				Color msaa_pixel;
				for (int s = 0; s < m_sample_scale; ++s)
				{
					const decimal px = (x - h_rw + DecimalRandom::dice() - 0.5) / rw;
					const decimal py = (y - h_rh + DecimalRandom::dice() - 0.5) / rh;
					
					m_camera->generate_ray(cray, px, py);
					Color clr_shade;
					if (_radiance(clr_shade, scene, cray, 0))
					{
						hit = true;
						clr_shade.clamp();
						msaa_pixel += clr_shade / m_sample_scale;
					}
				}

				pixel += msaa_pixel / msaa_count;
			}

			if (hit)
			{
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
			quit = true;
		}
		else
		{
			retval = true;
			if ("default" == hit_info.mtrl->type())
			{
				const DefaultMaterial* mtrl = 
					static_cast<const DefaultMaterial*>(hit_info.mtrl);

				Vector3 nl = hit_info.inters.m_normal.dot(hit_info.inters.m_ray_in.m_direction) < 0 ?
					hit_info.inters.m_normal : hit_info.inters.m_normal * -1;

				if (mtrl->has_property(DefaultMaterial::DIFFUSE))
				{
					Color trace;
					if (_radiance(trace, scene, _random_ray(nl, hit_info.inters.m_hit_point), depth + 1))
					{
						output += mtrl->get_color(DefaultMaterial::DIFFUSE) * trace;
					}
				}

				if (mtrl->has_property(DefaultMaterial::SPECULAR))
				{
					Color trace;
					if (_radiance(trace, scene, hit_info.inters.m_ray_in, depth + 1))
					{
						output += mtrl->get_color(DefaultMaterial::SPECULAR) * trace;
					}
				}

				if (mtrl->has_property(DefaultMaterial::REFRACT))
				{
					// TODO: calculate refract.
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

Math::Ray3 RdrrPathTracing::_reflect_ray(const Math::Ray3& ray_in, const Math::Vector3& normal) const
{
	return Ray3(ray_in.m_origin, ray_in.m_direction - normal * 2 * normal.dot(ray_in.m_direction));
}