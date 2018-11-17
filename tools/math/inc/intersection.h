/* ****************************************************************************
intersection.h
-------------------------------------------------------------------------------

Copyright (c) 2017, Tain L.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**************************************************************************** */

#pragma once

#include "my-prerequisites.h"
#include "vector3.h"
#include "point3.h"
#include "ray3.h"
#include "color.h"

namespace Light
{
	namespace Math
	{
		class Intersection
		{
		public:
			Intersection();
			Intersection(const Ray3& ray_in);
			Intersection(const Ray3& ray_in, const Point3& hit_point,
				const Vector3& normal, const decimal& travel);

			inline void refresh_travel()
			{
				m_travel = sqrt((m_ray_in.m_origin.m_x - m_hit_point.m_x)*(m_ray_in.m_origin.m_x - m_hit_point.m_x) +
					(m_ray_in.m_origin.m_y - m_hit_point.m_y) * (m_ray_in.m_origin.m_y - m_hit_point.m_y) +
					(m_ray_in.m_origin.m_z - m_hit_point.m_z) * (m_ray_in.m_origin.m_z - m_hit_point.m_z));
			}

			inline void transform(const Matrix4& matrix)
			{
				m_hit_point =  m_hit_point * matrix;
				m_normal = m_normal * matrix;
				m_normal.normalize();
				m_ray_in.transform(matrix);
				refresh_travel();
			}

		public:

			Ray3	m_ray_in;
			Point3	m_hit_point;
			Vector3	m_normal;
			decimal m_travel;
		};

		inline Intersection::Intersection()
			: m_ray_in(Point3(), Vector3())
			, m_hit_point(infinity, infinity, infinity)
			, m_travel(infinity)
		{}

		inline Intersection::Intersection(const Ray3& ray_in)
			: m_ray_in(ray_in)
			, m_hit_point(infinity, infinity, infinity)
			, m_travel(infinity)
		{}

		inline Intersection::Intersection(const Ray3& ray_in, const Point3& hit_point,
			const Vector3& normal, const decimal& travel)
			: m_ray_in(ray_in)
			, m_hit_point(hit_point)
			, m_normal(normal), m_travel(travel)
		{}
	}
}
