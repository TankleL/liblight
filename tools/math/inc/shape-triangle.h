/* ****************************************************************************
shape-triangle.h
-------------------------------------------------------------------------------

Copyright (c) 2018, Tain L.
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
#include "shape.h"

namespace Light
{
	namespace Math
	{
		class ShapeTriangle : public Shape
		{
		public:
			ShapeTriangle(const Point3& vt0, const Point3& vt1, const Point3& vt2);

		public:
			virtual bool intersected(Intersection& inters, const Ray3& ray_in) override;

		protected:
			bool _ray_cross_triangle(const Ray3& ray,
				const Point3& v0, const Point3& v1, const Point3& v2,
				decimal& travel, decimal& u, decimal& v) const;

		protected:
			Point3	m_vertices[3];
		};

		inline ShapeTriangle::ShapeTriangle(const Point3& vt0, const Point3& vt1, const Point3& vt2)
		{
			m_vertices[0] = vt0;
			m_vertices[1] = vt1;
			m_vertices[2] = vt2;
		}

		inline bool ShapeTriangle::intersected(Intersection& inters, const Ray3& ray_in)
		{
			bool res = false;

			decimal		t, u, v;

			if (_ray_cross_triangle(ray_in,
				m_vertices[0],
				m_vertices[1],
				m_vertices[2],
				t,
				u,
				v) &&
				t > 0.0)
			{
				res = true;

				inters.m_ray_in = ray_in;
				inters.m_hit_point = ray_in.on_ray(t);
				inters.m_travel = t;
				
				Vector3 edg1 = m_vertices[1] - m_vertices[0];
				Vector3 edg2 = m_vertices[2] - m_vertices[1];
				inters.m_normal = edg1.cross(edg2);
				inters.m_normal.normalize();
			}
			
			return res;
		}

		inline bool ShapeTriangle::_ray_cross_triangle(const Ray3& ray,
			const Point3& v0, const Point3& v1, const Point3& v2,
			decimal& travel, decimal& u, decimal& v) const
		{
			Vector3 E1(v1);
			E1 -= v0;

			Vector3 E2(v2);
			E2 -= v0;

			Vector3 P(ray.m_direction);
			P = P.cross(E2);

			// determinant
			float det = E1.dot(P);

			// keep det > 0, modify T accordingly
			Vector3 T;
			if (det > 0)
			{
				T = ray.m_origin;
				T -= v0;
			}
			else
			{
				T = v0;
				T -= ray.m_origin;
				det = -det;
			}

			// If determinant is near zero, ray lies in plane of triangle
			if (det < epsilon)
			{
				return false;
			}

			// Calculate u and make sure u <= 1
			u = T.dot(P);
			if (u < 0.0f || u > det)
			{
				return false;
			}

			// Q
			Vector3 Q(T);
			Q = Q.cross(E1);

			// Calculate v and make sure u + v <= 1
			v = ray.m_direction.dot(Q);
			if (v < 0.0f || u + v > det)
			{
				return false;
			}

			// Calculate t, scale parameters, ray intersects triangle
			travel = E2.dot(Q);

			decimal fInvDet = 1.0f / det;
			travel *= fInvDet;
			u *= fInvDet;
			v *= fInvDet;

			return true;
		}

	} // namespace Math
} // namespace Light
