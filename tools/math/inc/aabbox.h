/* ****************************************************************************
aabbox.h
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

#if !defined(LIGHT_MATHINC_AABBOX_H)
#define LIGHT_MATHINC_AABBOX_H

namespace Light
{
	namespace Math
	{
		class AABBox final
		{
		public:
			AABBox();
			AABBox(const Point3& min, const Point3& max);
			AABBox(const AABBox& rhs);
			AABBox(AABBox&& rhs);

			AABBox& operator=(const AABBox& rhs);
			AABBox& operator=(AABBox&& rhs);

		public:
			decimal width() const;
			decimal height() const;
			decimal depth() const;

			void add_point(const Point3& point);
			void transform(const Matrix4& matrix);
			bool is_empty() const;
			void clear();

			Point3 left_bottom_near() const;
			Point3 left_top_near() const;
			Point3 right_bottom_near() const;
			Point3 right_top_near() const;
			Point3 left_bottom_far() const;
			Point3 left_top_far() const;
			Point3 right_bottom_far() const;
			Point3 right_top_far() const;

			Point3 corner(index corner_idx) const;
			Point3 center() const;
			Point3 half() const;

			Point3& min();
			const Point3& min() const;
			Point3& max();
			const Point3& max() const;

		private:
			Point3		m_min;
			Point3		m_max;
			Point3		m_tmin;
			Point3		m_tmax;
		}; // class AABBox final

		inline AABBox::AABBox() :
			m_min(0, 0, 0),
			m_max(0, 0, 0),
			m_tmin(0, 0, 0),
			m_tmax(0, 0, 0)
		{}

		inline AABBox::AABBox(const Point3& min, const Point3& max) :
			m_min(min), m_max(max), m_tmin(min), m_tmax(max)
		{}

		inline AABBox::AABBox(const AABBox& rhs) :
			m_min(rhs.m_min), m_max(rhs.m_max),
			m_tmin(rhs.m_tmin), m_tmax(rhs.m_tmax)
		{}

		inline AABBox::AABBox(AABBox&& rhs) :
			m_min(std::move(rhs.m_min)),
			m_max(std::move(rhs.m_max)),
			m_tmin(std::move(rhs.m_tmin)),
			m_tmax(std::move(rhs.m_tmax))
		{}

		inline AABBox& AABBox::operator=(const AABBox& rhs)
		{
			m_min = rhs.m_min;
			m_max = rhs.m_max;
			m_tmin = rhs.m_tmin;
			m_tmax = rhs.m_tmax;
			return *this;
		}

		inline AABBox& AABBox::operator=(AABBox&& rhs)
		{
			m_min = std::move(rhs.m_min);
			m_max = std::move(rhs.m_max);
			m_tmin = std::move(rhs.m_tmin);
			m_tmax = std::move(rhs.m_tmax);
			return *this;
		}

		inline decimal AABBox::width() const
		{
			return m_tmax.m_x - m_tmin.m_x;
		}

		inline decimal AABBox::height() const
		{
			return m_tmax.m_y - m_tmin.m_y;
		}

		inline decimal AABBox::depth() const
		{
			return m_tmax.m_z - m_tmin.m_z;
		}

		/**
		If you finished updating the points in this aabbox by calling this method,
		you MUST call the method 'transform' as soon as you can.
		*/
		inline void AABBox::add_point(const Point3& point)
		{
			if (point.m_x < m_min.m_x)  m_tmin.m_x = m_min.m_x = point.m_x;
			if (point.m_y < m_min.m_y)	m_tmin.m_y = m_min.m_y = point.m_y;
			if (point.m_z < m_min.m_z)	m_tmin.m_z = m_min.m_z = point.m_z;

			if (point.m_x > m_max.m_x)	m_tmin.m_x = m_max.m_x = point.m_x;
			if (point.m_y > m_max.m_y)	m_tmin.m_y = m_max.m_y = point.m_y;
			if (point.m_z > m_max.m_z)	m_tmin.m_z = m_max.m_z = point.m_z;
		}

		inline void AABBox::transform(const Matrix4& matrix)
		{
			Point3 vertices[8] = {
				m_min * matrix,										// left_bottom_near
				Point3(m_min.m_x, m_max.m_y, m_min.m_z) * matrix,	// left_top_near
				Point3(m_max.m_x, m_min.m_y, m_min.m_z) * matrix,	// right_bottom_near
				Point3(m_max.m_x, m_max.m_y, m_min.m_z) * matrix,	// right_top_near
				Point3(m_min.m_x, m_min.m_y, m_max.m_z) * matrix,	// left_bottom_far
				Point3(m_min.m_x, m_max.m_y, m_max.m_z) * matrix,	// left_top_far
				Point3(m_max.m_x, m_min.m_y, m_max.m_z) * matrix,	// right_bottom_far
				m_max * matrix										// right_top_far
			};

			m_tmin = std::move(Point3(0, 0, 0));
			m_tmax = std::move(Point3(0, 0, 0));

			for (auto& point : vertices)
			{
				if (point.m_x < m_tmin.m_x)	m_tmin.m_x = point.m_x;
				if (point.m_y < m_tmin.m_y)	m_tmin.m_y = point.m_y;
				if (point.m_z < m_tmin.m_z)	m_tmin.m_z = point.m_z;

				if (point.m_x > m_tmax.m_x)	m_tmax.m_x = point.m_x;
				if (point.m_y > m_tmax.m_y)	m_tmax.m_y = point.m_y;
				if (point.m_z > m_tmax.m_z)	m_tmax.m_z = point.m_z;
			}
		}

		inline bool AABBox::is_empty() const
		{
			return (decimal_equal(m_min.m_x, m_max.m_x) &&
				decimal_equal(m_min.m_y, m_max.m_y) &&
				decimal_equal(m_min.m_z, m_max.m_z));
		}

		inline void AABBox::clear()
		{
			m_max = std::move(Point3(0, 0, 0));
			m_min = std::move(Point3(0, 0, 0));
			m_tmax = std::move(Point3(0, 0, 0));
			m_tmin = std::move(Point3(0, 0, 0));
		}

		inline Point3 AABBox::left_bottom_near() const
		{
			return m_tmin;
		}

		inline Point3 AABBox::left_top_near() const
		{
			return Point3(m_tmin.m_x, m_tmax.m_y, m_tmin.m_z);
		}

		inline Point3 AABBox::right_bottom_near() const
		{
			return Point3(m_tmax.m_x, m_tmin.m_y, m_tmin.m_z);
		}

		inline Point3 AABBox::right_top_near() const
		{
			return Point3(m_tmax.m_x, m_tmax.m_y, m_tmin.m_z);
		}

		inline Point3 AABBox::left_bottom_far() const
		{
			return Point3(m_tmin.m_x, m_tmin.m_y, m_tmax.m_z);
		}

		inline Point3 AABBox::left_top_far() const
		{
			return Point3(m_tmin.m_x, m_tmax.m_y, m_tmax.m_z);
		}

		inline Point3 AABBox::right_bottom_far() const
		{
			return Point3(m_tmax.m_x, m_tmin.m_y, m_tmax.m_z);
		}

		inline Point3 AABBox::right_top_far() const
		{
			return m_tmax;
		}

		/**
		corner_idx must be in [0, 7]
		*/
		inline Point3 AABBox::corner(index corner_idx) const
		{
			assert(corner_idx < 8);
			return Point3((corner_idx & 1UL) ? m_tmax.m_x : m_tmin.m_x,
				(corner_idx & 2UL) ? m_tmax.m_y : m_tmin.m_y,
				(corner_idx & 4UL) ? m_tmax.m_z : m_tmin.m_z);
		}

		inline Point3 AABBox::center() const
		{
			Point3 res = std::move(m_tmin + m_tmax);
			res *= 0.5f;
			return res;
		}

		inline Point3 AABBox::half() const
		{
			Point3 res = std::move(m_tmax - m_tmin);
			res *= 0.5f;
			return res;
		}

		inline Point3& AABBox::min()
		{
			return m_tmin;
		}

		inline const Point3& AABBox::min() const
		{
			return m_tmin;
		}

		inline Point3& AABBox::max()
		{
			return m_tmax;
		}

		inline const Point3& AABBox::max() const
		{
			return m_tmax;
		}
	} //namespace Math
} // namespace LIGHT

#endif // LIGHT_MATHINC_AABBOX_H