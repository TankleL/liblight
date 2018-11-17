/* ****************************************************************************
vector3.h
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

namespace Light
{
	namespace Math
	{
		class Vector3
		{
		public:
			Vector3();
			Vector3(decimal x, decimal y, decimal z);
			Vector3(const Vector3& rhs);
			Vector3(Vector3&& rhs);

		public:
			decimal& operator[](uint32 idx);
			decimal operator[](uint32 idx) const;
			Vector3& operator=(const Vector3& rhs);
			Vector3& operator=(Vector3&& rhs);
			bool operator==(const Vector3& rhs) const;
			Vector3& operator*=(decimal times);
			Vector3& operator/=(decimal div);
			Vector3& operator+=(const Vector3& rhs);
			Vector3& operator-=(const Vector3& rhs);
			decimal length_square() const;
			decimal length() const;
			decimal normalize();
			decimal dot(const Vector3& rhs) const;
			Vector3 cross(const Vector3& rhs) const;

		public:
			union
			{
				decimal		m_data[4];
				struct
				{
					decimal	m_x;
					decimal m_y;
					decimal m_z;
					decimal m_w;
				}; // struct
			}; // union
		}; // class Vector3

		inline Vector3::Vector3() :
			m_data{ 0.0f }
		{}

		inline Vector3::Vector3(decimal x, decimal y, decimal z) :
			m_x(x), m_y(y), m_z(z), m_w(0.0f)
		{}

		inline Vector3::Vector3(const Vector3& rhs) :
			m_x(rhs.m_x), m_y(rhs.m_y), m_z(rhs.m_z), m_w(0.0f)
		{}

		inline Vector3::Vector3(Vector3&& rhs) :
			m_x(rhs.m_x),
			m_y(rhs.m_y),
			m_z(rhs.m_z),
			m_w(0.0f)
		{}

		inline Vector3& Vector3::operator=(const Vector3& rhs)
		{
			m_x = rhs.m_x;
			m_y = rhs.m_y;
			m_z = rhs.m_z;
			return *this;
		}

		inline Vector3& Vector3::operator=(Vector3&& rhs)
		{
			m_x = rhs.m_x;
			m_y = rhs.m_y;
			m_z = rhs.m_z;
			m_w = 0.0f;
			return *this;
		}

		inline bool Vector3::operator==(const Vector3& rhs) const
		{
			return decimal_equal(m_x, rhs.m_x) &&
				decimal_equal(m_y, rhs.m_y) &&
				decimal_equal(m_z, rhs.m_z) &&
				decimal_equal(m_w, rhs.m_w);
		}

		inline decimal& Vector3::operator[](uint32 idx)
		{
			return m_data[idx];
		}

		inline decimal Vector3::operator[](uint32 idx) const
		{
			return m_data[idx];
		}

		inline Vector3& Vector3::operator*=(decimal times)
		{
			m_x *= times;
			m_y *= times;
			m_z *= times;
			return *this;
		}

		inline Vector3& Vector3::operator/=(decimal div)
		{
			m_x /= div;
			m_y /= div;
			m_z /= div;
			return *this;
		}

		inline Vector3& Vector3::operator+=(const Vector3& rhs)
		{
			m_x += rhs.m_x;
			m_y += rhs.m_y;
			m_z += rhs.m_z;
			return *this;
		}

		inline Vector3& Vector3::operator-=(const Vector3& rhs)
		{
			m_x -= rhs.m_x;
			m_y -= rhs.m_y;
			m_z -= rhs.m_z;
			return *this;
		}

		inline decimal Vector3::length_square() const
		{
			return (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
		}

		inline decimal Vector3::length() const
		{
			return std::sqrt(length_square());
		}

		inline decimal Vector3::normalize()
		{
			decimal len = length();
			(*this) /= len;
			return len;
		}

		inline decimal Vector3::dot(const Vector3& rhs) const
		{
			// In cartesian coordinates, it simplifies to this simple calculation:
			return m_x * rhs.m_x + m_y * rhs.m_y + m_z * rhs.m_z;
		}

		inline Vector3 Vector3::cross(const Vector3& rhs) const
		{
			return Vector3(m_y * rhs.m_z - m_z * rhs.m_y,
				m_z * rhs.m_x - m_x * rhs.m_z,
				m_x * rhs.m_y - m_y * rhs.m_x);
		}

		inline Vector3 operator+(const Vector3& left, const Vector3& right)
		{
			return Vector3(left.m_x + right.m_x,
				left.m_y + right.m_y,
				left.m_z + right.m_z);
		}

		inline Vector3 operator-(const Vector3& left, const Vector3& right)
		{
			return Vector3(left.m_x - right.m_x,
				left.m_y - right.m_y,
				left.m_z - right.m_z);
		}

		inline Vector3 operator*(const Vector3& v1, decimal times)
		{
			Vector3 res(v1);
			res *= times;
			return res;
		}

		inline Vector3 operator*(decimal times, const Vector3& v1)
		{
			Vector3 res(v1);
			res *= times;
			return res;
		}

		inline Vector3 operator/(const Vector3& v1, decimal div)
		{
			Vector3 res(v1);
			res /= div;
			return res;
		}
	} // namespace Math
} // namespace Light
