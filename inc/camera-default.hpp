/* ****************************************************************************
@module default-camera

@brief this is a pinhole module camera.
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

#include "camera.hpp"

namespace Light
{
	class LIGHT_API DefaultCamera : public Camera
	{
	public:
		DefaultCamera(Math::decimal filmplane_width = 16.0f,
			Math::decimal filmplane_height = 9.0f,
			Math::decimal filmplane_depth = 5.0f);
		virtual ~DefaultCamera();

	public:
		/**
		@interface: generate_ray
		@param: x_offset means the logic x-position that the ray intersects with the film plane. range is [-0.5, 0.5]
		@param: y_offset means the logic y-position that the ray intersects with the film plane. range is [-0.5, 0.5]
		@return: a camera ray
		*/
		virtual void generate_ray(Math::Ray3& cray, Math::decimal x_offset, Math::decimal y_offset) override;

	protected:
		Math::decimal	m_filmplane_width;
		Math::decimal	m_filmplane_height;
		Math::decimal	m_filmplane_depth;
	};
}
