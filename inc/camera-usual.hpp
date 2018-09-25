/* ****************************************************************************
@module usual-camera

@brief this is a usual camera, which supports Depth-of-Field.
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

#include "prerequisites.hpp"
#include "camera-default.hpp"

namespace Light
{
	class LIGHT_API UsualCamera : public DefaultCamera
	{
	public:
		UsualCamera(
			Math::decimal filmplane_width = 16.0f,
			Math::decimal filmplane_height = 9.0f,
			Math::decimal filmplane_depth = 5.0f,
			Math::decimal focus = 30.0f,
			Math::decimal aperture_radius = 1.0f
		);

		virtual ~UsualCamera();

	public:
		virtual void generate_ray(Math::Ray3& cray, Math::decimal x_offset, Math::decimal y_offset) override;

	protected:
		Math::decimal	m_lens_focus;
		Math::decimal	m_lens_aperture_radius;
	};
}
