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

namespace RdrrPathTracingUtil
{
	struct DoubleRay
	{
		DoubleRay()
			: valid_ray_count(0)
		{}

		Math::Ray3 r1;
		Math::Ray3 r2;

		int valid_ray_count;
	};

	inline Math::Ray3 random_ray(
		const Math::Vector3& normal,
		const Math::Point3& hit_pos)
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
		return Ray3(hit_pos + dir * epsilon, dir);
	}

	inline Math::Ray3 reflect_ray(
		const Math::Ray3& ray_in,
		const Math::Point3& hit_point,
		const Math::Vector3& normal)
	{
		Vector3 dir = ray_in.m_direction - normal * 2 * normal.dot(ray_in.m_direction);
		return Ray3(hit_point + dir * epsilon, dir);
	}

	inline DoubleRay refract_ray(
		decimal ior,
		const Math::Ray3& ray_in,
		const Math::Point3& hit_point,
		const Math::Vector3& nr)
	{
		DoubleRay out;

		const decimal idn = ray_in.m_direction.dot(nr);
		const decimal cost_sq = 1.0 - (ior * ior) * (1 - idn * idn);

		if (cost_sq < 0) // Total internal reflection
		{
			out.valid_ray_count = 1;
			out.r1 = reflect_ray(ray_in, hit_point, nr);
		}
		else
		{
			out.valid_ray_count = 2;
			out.r1 = reflect_ray(ray_in, hit_point, nr);

			out.r2.m_direction =
				ior * ray_in.m_direction -
				nr * (ior * idn + sqrt(cost_sq));
			out.r2.m_direction.normalize();
			out.r2.m_origin = hit_point + out.r2.m_direction * epsilon;
		}

		return out;
	}
}

RdrrPathTracing::RdrrPathTracing(int sample_scale,
	int max_radiance_depth)
	: m_sample_scale(sample_scale)
	, m_max_radiance_depth(max_radiance_depth)
	, m_cur_ior(1, 1, 1)
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
		fflush(stdout);

#pragma omp parallel for schedule(dynamic, 1) private(cray)
		for (int x = 0; x < (int)rw; ++x)
		{
			Color pixel;
			Color c_shade;
			for (int s = 0; s < m_sample_scale; ++s)
			{
				const decimal px = ((decimal)x - h_rw + DecimalRandom::dice() - 0.5) / rw;
				const decimal py = (y - h_rh + DecimalRandom::dice() - 0.5) / rh;

				m_camera->generate_ray(cray, px, py);
				Color s_shade;
				pixel += _radiance(scene, cray, 0) / (decimal)m_sample_scale;
			}

			pixel.clamp();
			output.set_pixel((int)x, (int)y, pixel);
		}
	}
	printf("\n");
}

Math::Color RdrrPathTracing::_radiance(const Scene& scene, const Math::Ray3& ray_in, int depth)
{
	using namespace RdrrPathTracingUtil;

	Math::Color output;
	bool quit = false;
	
	Scene::HitInfo hit_info;
	quit = !scene.hit_detect(hit_info, ray_in);

	if (!quit)
	{	
		if (depth > m_max_radiance_depth)
		{ // Russian Roulette
			// Stop the recursion randomly based on the surface reflectivity.
			// TODO: impl R.R.
			return m_back_clr;
		}
		else
		{
			++depth;
			if ("default" == hit_info.mtrl->type())
			{
				const DefaultMaterial* mtrl = 
					static_cast<const DefaultMaterial*>(hit_info.mtrl);

				const Point3& x = hit_info.inters.m_hit_point;
				const Vector3& n = hit_info.inters.m_normal;
				const Ray3& r = ray_in;

				bool is_going_in = n.dot(r.m_direction) < 0;

				if (mtrl->has_property(DefaultMaterial::DIFFUSE))
				{
					output += mtrl->get_color(DefaultMaterial::DIFFUSE) *
						_radiance(scene, random_ray(n, x), depth);
				}

				if (mtrl->has_property(DefaultMaterial::SPECULAR) && is_going_in)
				{
					output += mtrl->get_color(DefaultMaterial::SPECULAR) *
						_radiance(scene, reflect_ray(ray_in, x, n), depth);
				}

				if (mtrl->has_property(DefaultMaterial::REFRACT) &&
					mtrl->has_property(DefaultMaterial::IOR))
				{
					const Vector3 n_o = is_going_in ? n : -1 * n;	// normal - outside of shape.

					DoubleRay dr = refract_ray(
						is_going_in ?
						1.0/ mtrl->get_color(DefaultMaterial::IOR).m_r :
						mtrl->get_color(DefaultMaterial::IOR).m_r,
						r, x, n_o);

					if (dr.valid_ray_count == 1)
					{
						output += mtrl->get_color(DefaultMaterial::REFRACT) *
							_radiance(scene, dr.r1, depth);
					}
					else if (dr.valid_ray_count == 2)
					{
//						output += mtrl->get_color(DefaultMaterial::REFRACT) *
//							_radiance(scene, dr.r1, depth) * 0.5;

						output += mtrl->get_color(DefaultMaterial::REFRACT) *
							_radiance(scene, dr.r2, depth);
					}
				}

				if (mtrl->has_property(DefaultMaterial::EMISSIVE))
				{
					output += mtrl->get_color(DefaultMaterial::EMISSIVE);
				}
			}
		}
	}

	return output;
}
