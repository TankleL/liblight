/* ****************************************************************************
triangleface.h
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


#if !defined(LIGHT_MATHINC_TRIANGLEFACE_H)
#define LIGHT_MATHINC_TRIANGLEFACE_H

#include "my-prerequisites.h"

namespace Light
{
	namespace Math
	{
		class TriangleFace
		{
		public:	
			TriangleFace(index v0, index v1, index v2);
			TriangleFace(const TriangleFace& rhs);
			TriangleFace(TriangleFace&& rhs);

			TriangleFace& operator=(const TriangleFace& rhs);
			TriangleFace& operator=(TriangleFace&& rhs);

		public:
			index m_vertex_idx[3];
		};

		inline TriangleFace::TriangleFace(index v0, index v1, index v2)
		{
			m_vertex_idx[0] = v0;
			m_vertex_idx[1] = v1;
			m_vertex_idx[2] = v2;
		}

		inline TriangleFace::TriangleFace(const TriangleFace& rhs)
		{
			m_vertex_idx[0] = rhs.m_vertex_idx[0];
			m_vertex_idx[1] = rhs.m_vertex_idx[1];
			m_vertex_idx[2] = rhs.m_vertex_idx[2];
		}

		inline TriangleFace::TriangleFace(TriangleFace&& rhs)
		{
			m_vertex_idx[0] = std::move(rhs.m_vertex_idx[0]);
			m_vertex_idx[1] = std::move(rhs.m_vertex_idx[1]);
			m_vertex_idx[2] = std::move(rhs.m_vertex_idx[2]);
		}

		inline TriangleFace& TriangleFace::operator=(const TriangleFace& rhs)
		{
			m_vertex_idx[0] = rhs.m_vertex_idx[0];
			m_vertex_idx[1] = rhs.m_vertex_idx[1];
			m_vertex_idx[2] = rhs.m_vertex_idx[2];
			return *this;
		}

		inline TriangleFace& TriangleFace::operator=(TriangleFace&& rhs)
		{
			m_vertex_idx[0] = std::move(rhs.m_vertex_idx[0]);
			m_vertex_idx[1] = std::move(rhs.m_vertex_idx[1]);
			m_vertex_idx[2] = std::move(rhs.m_vertex_idx[2]);
			return *this;
		}
	}
}

#endif // ! LIGHT_MATHINC_TRIANGLEFACE_H
