/* ****************************************************************************
color.h
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


#if !defined(LIGHT_MATHINC_COLOR_H)
#define LIGHT_MATHINC_COLOR_H

#include "my-prerequisites.h"

namespace Light
{
	namespace Math
	{
		struct Color
		{
			decimal m_r, m_g, m_b;

			Color() : m_r(0.0f), m_g(0.0f), m_b(0.0f) { }
			Color(const Color& c) : m_r(c.m_r), m_g(c.m_g), m_b(c.m_b) { }
			Color(decimal r, decimal g, decimal b) : m_r(r), m_g(g), m_b(b) { }
			explicit Color(decimal f) : m_r(f), m_g(f), m_b(f) { }

			void clamp(decimal min = 0.0f, decimal max = 1.0f)
			{
				m_r = std::max(min, std::min(max, m_r));
				m_g = std::max(min, std::min(max, m_g));
				m_b = std::max(min, std::min(max, m_b));
			}

			Color& operator =(const Color& c)
			{
				m_r = c.m_r;
				m_g = c.m_g;
				m_b = c.m_b;
				return *this;
			}

			Color& operator +=(const Color& c)
			{
				m_r += c.m_r;
				m_g += c.m_g;
				m_b += c.m_b;
				return *this;
			}

			Color& operator -=(const Color& c)
			{
				m_r -= c.m_r;
				m_g -= c.m_g;
				m_b -= c.m_b;
				return *this;
			}

			Color& operator *=(const Color& c)
			{
				m_r *= c.m_r;
				m_g *= c.m_g;
				m_b *= c.m_b;
				return *this;
			}

			Color& operator /=(const Color& c)
			{
				m_r /= c.m_r;
				m_g /= c.m_g;
				m_b /= c.m_b;
				return *this;
			}

			Color& operator *=(decimal f)
			{
				m_r *= f;
				m_g *= f;
				m_b *= f;
				return *this;
			}

			Color& operator /=(decimal f)
			{
				m_r /= f;
				m_g /= f;
				m_b /= f;
				return *this;
			}
		};


		inline Color operator +(const Color& c1, const Color& c2)
		{
			return Color(c1.m_r + c2.m_r,
				c1.m_g + c2.m_g,
				c1.m_b + c2.m_b);
		}


		inline Color operator -(const Color& c1, const Color& c2)
		{
			return Color(c1.m_r - c2.m_r,
				c1.m_g - c2.m_g,
				c1.m_b - c2.m_b);
		}


		inline Color operator *(const Color& c1, const Color& c2)
		{
			return Color(c1.m_r * c2.m_r,
				c1.m_g * c2.m_g,
				c1.m_b * c2.m_b);
		}


		inline Color operator /(const Color& c1, const Color& c2)
		{
			return Color(c1.m_r / c2.m_r,
				c1.m_g / c2.m_g,
				c1.m_b / c2.m_b);
		}


		inline Color operator *(const Color& c, decimal f)
		{
			return Color(f * c.m_r,
				f * c.m_g,
				f * c.m_b);
		}


		inline Color operator *(decimal f, const Color& c)
		{
			return Color(f * c.m_r,
				f * c.m_g,
				f * c.m_b);
		}


		inline Color operator /(const Color& c, decimal f)
		{
			return Color(c.m_r / f,
				c.m_g / f,
				c.m_b / f);
		}
	} // namespace Math

} // namespace Light

#endif // LIGHT_MATHINC_COLOR_H
