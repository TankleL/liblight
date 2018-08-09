/* ****************************************************************************
ray3.h
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


#if !defined(LIGHT_MATHINC_RAY3_H)
#define LIGHT_MATHINC_RAY3_H

#include "my-prerequisites.h"
#include "vector3.h"
#include "point3.h"
#include "matrix4.h"

namespace Light
{
	namespace Math
	{
		class Ray3
		{
		public:			
			Ray3(const Point3& origin, const Vector3& direction);
			Ray3(const Ray3& rhs);
			Ray3(Ray3&& rhs);

			Ray3& operator=(const Ray3& rhs);
			Ray3& operator=(Ray3&& rhs);
			bool operator==(const Ray3& rhs) const;

			Ray3& transform(const Matrix4& matrix);
			Point3 on_ray(decimal travel) const;
			
		public:
			Point3		m_origin;
			Vector3		m_direction;
		};

		inline Ray3::Ray3(const Point3& origin, const Vector3& direction) :
			m_origin(origin),
			m_direction(direction)
		{}

		inline Ray3::Ray3(const Ray3& rhs) :
			m_origin(rhs.m_origin),
			m_direction(rhs.m_direction)
		{}

		inline Ray3::Ray3(Ray3&& rhs) :
			m_origin(rhs.m_origin),
			m_direction(rhs.m_direction)
		{}

		inline Ray3& Ray3::operator=(const Ray3& rhs)
		{
			m_origin = rhs.m_origin;
			m_direction = rhs.m_direction;
			return *this;
		}

		inline Ray3& Ray3::operator=(Ray3&& rhs)
		{
			*this = std::move(rhs);
			return *this;
		}

		inline bool Ray3::operator==(const Ray3& rhs) const
		{
			return m_origin == rhs.m_origin &&
				m_direction == rhs.m_direction;
		}

		inline Ray3& Ray3::transform(const Matrix4& matrix)
		{
			m_origin = m_origin * matrix;
			m_direction = m_direction * matrix;
			m_direction.normalize();
			return *this;
		}

		inline Point3 Ray3::on_ray(decimal travel) const
		{
			return std::move(m_origin + m_direction * travel);
		}

		class Ray3Utils
		{
		public:
			static Ray3 make_ray(const Point3& pt_from, const Point3& pt_to);
		};

	} // namespace Math
} // namespace Spears


#endif // LIGHT_MATHINC_RAY3_H