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

#pragma once

#include "prerequisites.hpp"
#include "scene.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include "../tools/math/inc/mathinc.h"

namespace Light
{
	class LIGHT_API RdrrPathTracing : public Renderer
	{
	public:
		RdrrPathTracing(int sample_scale = 8,
			int max_radiance_depth = 8);

	public:
		virtual void render(Texture2D& output, const Scene& scene) override;

	public:
		void set_camera(Camera* camera);

	protected:
		Math::Color _radiance(const Scene& scene, const Math::Ray3& ray_in, int depth);

	protected:
		Camera*	m_camera;
		int		m_max_radiance_depth;
		int		m_sample_scale;

	protected:
		Math::Color m_back_clr;
	};


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
			using namespace Math;

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
			using namespace Math;

			Vector3 dir = ray_in.m_direction - normal * 2 * normal.dot(ray_in.m_direction);
			return Ray3(hit_point + dir * epsilon, dir);
		}

		inline DoubleRay refract_ray(
			Math::decimal ior,
			const Math::Ray3& ray_in,
			const Math::Point3& hit_point,
			const Math::Vector3& nr)
		{
			using namespace Math;

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

		inline Math::decimal pixel_turbulent(Math::decimal range = 1.0)
		{
			using namespace Math;

			const decimal half_range = range * 0.5;
			decimal r = DecimalRandom::dice(range) - half_range;
			return (r >= 0 ? -r : r) + half_range;
		}
	}

}
