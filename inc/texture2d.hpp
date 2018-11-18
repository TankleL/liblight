/* ****************************************************************************
texture2d.h
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

#include "prerequisites.hpp"
#include "../tools/math/inc/mathinc.h"

namespace Light
{
	class LIGHT_API Texture2D
	{
	public:
		Texture2D(const Math::Resolution& resolution);
		virtual ~Texture2D();

	public:
		Math::Resolution get_resolution() const;
		Math::Color get_pixel(int x, int y) const;
		const Light::byte* get_buffer() const;
		void set_pixel(int x, int y, const Math::Color& value);
			
	protected:
		Math::Resolution				m_resolution;
		Light::byte*					m_p_pixels;		// R8G8B8 format, align = 1.
	};

	inline Texture2D::Texture2D(const Math::Resolution& resolution) :
		m_resolution(resolution),
		m_p_pixels(new Light::byte[resolution.get_width() * resolution.get_height() * 3])  // R8G8B8 format, align = 1.
	{}

	inline Texture2D::~Texture2D()
	{}

	inline Math::Resolution Texture2D::get_resolution() const
	{
		return m_resolution;
	}

	inline Math::Color Texture2D::get_pixel(int x, int y) const
	{
		assert(m_resolution.get_width() != 0 && m_resolution.get_height() != 0);
		assert(x >= 0 && x <= m_resolution.get_width());
		assert(y >= 0 && y <= m_resolution.get_height());

		Light::byte* p_pixel = m_p_pixels + (x + y * m_resolution.get_width()) * 3;

		Math::Color reval;
		reval.m_r = (float)p_pixel[0] / 255.0f;
		reval.m_g = (float)p_pixel[1] / 255.0f;
		reval.m_b = (float)p_pixel[2] / 255.0f;

		return reval;
	}

	inline const Light::byte* Texture2D::get_buffer() const
	{
		return m_p_pixels;
	}

	inline void Texture2D::set_pixel(int x, int y, const Math::Color& value)
	{
		assert(m_resolution.get_width() != 0 && m_resolution.get_height() != 0);
		assert(x >= 0 && x <= m_resolution.get_width());
		assert(y >= 0 && y <= m_resolution.get_height());

		Light::byte* p_pixel = m_p_pixels + (x + y * m_resolution.get_width()) * 3;
		p_pixel[0] = value.m_r * 255;
		p_pixel[1] = value.m_g * 255;
		p_pixel[2] = value.m_b * 255;
	}
}
