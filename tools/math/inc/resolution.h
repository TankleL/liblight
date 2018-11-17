/* ****************************************************************************
resolution.h
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
		class Resolution
		{
		public:
			Resolution();
			Resolution(int width, int height);
			Resolution(const Resolution& rhs);
			Resolution(Resolution&& rhs);
			virtual ~Resolution();

			Resolution& operator=(const Resolution& rhs);
			Resolution& operator=(Resolution&& rhs);
			bool operator==(const Resolution& right);

		public:
			int get_width() const;
			int get_height() const;
			void set_width(int width);
			void set_height(int height);

		protected:
			int		m_width;
			int		m_height;
		};

		inline Resolution::Resolution() :
			m_width(0), m_height(0)
		{}

		inline Resolution::Resolution(int width, int height) :
			m_width(width), m_height(height)
		{}

		inline Resolution::Resolution(const Resolution& rhs) :
			m_width(rhs.m_width), m_height(rhs.m_height)
		{}

		inline Resolution::Resolution(Resolution&& rhs) :
			m_width(std::move(rhs.m_width)),
			m_height(std::move(rhs.m_height))
		{}

		inline Resolution::~Resolution()
		{}

		inline Resolution& Resolution::operator=(const Resolution& rhs)
		{
			m_width = rhs.m_width;
			m_height = rhs.m_height;
			return *this;
		}

		inline Resolution& Resolution::operator=(Resolution&& rhs)
		{
			m_width = std::move(rhs.m_width);
			m_height = std::move(rhs.m_height);
			return *this;
		}

		inline bool Resolution::operator==(const Resolution& right)
		{
			return (m_width == right.m_width && m_height == right.m_height);
		}

		inline int Resolution::get_width() const
		{
			return m_width;
		}

		inline int Resolution::get_height() const
		{
			return m_height;
		}

		inline void Resolution::set_width(int width)
		{
			m_width = width;
		}

		inline void Resolution::set_height(int height)
		{
			m_height = height;
		}
	}
}
