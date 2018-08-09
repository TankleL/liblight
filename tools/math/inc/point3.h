/* ****************************************************************************
point3.h
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

#if !defined(LIGHT_MATHINC_POINT3_H)
#define LIGHT_MATHINC_POINT3_H

#include "my-prerequisites.h"

#include "vector3.h"

namespace Light
{
	namespace Math
	{
		class Point3 : public Vector3
		{
		public:
			Point3();
			Point3(const Vector3& rhs);
			Point3(const Point3& rhs);
			Point3(Vector3&& rhs);
			Point3(Point3&& rhs);
			Point3(decimal x, decimal y, decimal z);

			Point3& operator=(const Point3& rhs);
			Point3& operator=(Point3&& rhs);
			bool operator==(const Point3& rhs) const;

			Point3& operator*=(decimal times);
			Point3& operator/=(decimal div);
		}; // class Point3

		inline Point3::Point3()
		{ m_w = 1.0f; }

		inline Point3::Point3(const Vector3& rhs) :
			Vector3(rhs)
		{ m_w = 1.0f; }

		inline Point3::Point3(const Point3& rhs) :
			Vector3(rhs)
		{ m_w = 1.0f; }

		inline Point3::Point3(Vector3&& rhs) :
			Vector3(rhs)
		{ m_w = 1.0f; }

		inline Point3::Point3(Point3&& rhs) :
			Vector3(rhs)
		{ m_w = 1.0f; }

		inline Point3::Point3(decimal x, decimal y, decimal z) :
			Vector3(x, y, z)
		{ m_w = 1.0f; }

		inline Point3& Point3::operator=(const Point3& rhs)
		{
			m_x = rhs.m_x;
			m_y = rhs.m_y;
			m_z = rhs.m_z;
			m_w = 1.0f;
			return *this;
		}

		inline Point3& Point3::operator=(Point3&& rhs)
		{
			m_x = std::move(rhs.m_x);
			m_y = std::move(rhs.m_y);
			m_z = std::move(rhs.m_z);
			m_w = 1.0f;
			return *this;
		}

		inline bool Point3::operator==(const Point3& rhs) const
		{
			return decimal_equal(m_x, rhs.m_x) &&
				decimal_equal(m_y, rhs.m_y) &&
				decimal_equal(m_z, rhs.m_z) &&
				decimal_equal(m_w, rhs.m_w);
		}

		inline Point3& Point3::operator*=(decimal times)
		{
			m_x *= times;
			m_y *= times;
			m_z *= times;
			return *this;
		}

		inline Point3& Point3::operator/=(decimal div)
		{
			m_x /= div;
			m_y /= div;
			m_z /= div;
			return *this;
		}

		inline Point3 operator+(const Point3& p, const Vector3& v)
		{
			Point3 res;
			res.m_x += v.m_x;
			res.m_y += v.m_y;
			res.m_z += v.m_z;
			return res;
		}

		inline Point3 operator+(const Vector3& v, const Point3& p)
		{
			Point3 res;
			res.m_x += v.m_x;
			res.m_y += v.m_y;
			res.m_z += v.m_z;
			return res;
		}

		inline Point3 operator+(const Point3& left, const Point3& right)
		{
			return Point3(left.m_x + right.m_x,
				left.m_y + right.m_y,
				left.m_z + right.m_z);
		}

		inline Point3 operator-(const Point3& left, const Point3& right)
		{
			return Point3(left.m_x - right.m_x,
				left.m_y - right.m_y,
				left.m_z - right.m_z);
		}
	} // namespace Math
} // namespace Spears


#endif // LIGHT_MATHINC_POINT3_H