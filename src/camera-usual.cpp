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

#include "api-dev-mod.hpp"

#include "camera-usual.hpp"

using namespace Light;
using namespace Light::Math;

UsualCamera::UsualCamera(
	Math::decimal filmplane_width /* = 16.0f */,
	Math::decimal filmplane_height /* = 9.0f */,
	Math::decimal filmplane_depth /* = 5.0f */,
	Math::decimal focus /* = 30.0f */,
	Math::decimal aperture_radius /* = 1.0f */ )
	: DefaultCamera(
		filmplane_width,
		filmplane_height,
		filmplane_depth)
{}

UsualCamera::~UsualCamera()
{}

void UsualCamera::generate_ray(Math::Ray3& cray, Math::decimal x_offset, Math::decimal y_offset)
{
	// calculate direction of the ray.
	Math::Vector3 right_bias = m_right;
	Math::Vector3 up_bias = m_up;
	right_bias *= (x_offset * m_filmplane_width);
	up_bias *= (y_offset * m_filmplane_height);
	Math::Vector3 dir = m_look;

	dir = m_look;
	dir *= m_filmplane_depth;
	dir += right_bias;
	dir += up_bias;
	dir.normalize();

	Math::Point3 pf = m_position + m_look * m_lens_focus;	// focus point

	// set origin of ray.
	cray.m_origin = m_position;
}