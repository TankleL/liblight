/* ****************************************************************************
default-camera
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

#include "api-dev-mod.hpp"
#include "../inc/camera-default.hpp"

using namespace Light;

DefaultCamera::DefaultCamera(Math::decimal filmplane_width,
	Math::decimal filmplane_height,
	Math::decimal filmplane_depth) :
	m_filmplane_width(filmplane_width),
	m_filmplane_height(filmplane_height),
	m_filmplane_depth(filmplane_depth)
{}

DefaultCamera::~DefaultCamera()
{}

/**
@interface: generate_ray
@param: x_offset means the logic x-position that the ray intersects with the film plane. range is [-0.5, 0.5]
@param: y_offset means the logic y-position that the ray intersects with the film plane. range is [-0.5, 0.5]
@return: a camera ray
*/
void DefaultCamera::generate_ray(Math::Ray3& cray, Math::decimal x_offset, Math::decimal y_offset)
{
	// calculate direction of the ray.
	Math::Vector3 right_bias = m_right;
	Math::Vector3 up_bias = m_up;
	right_bias *= (x_offset * m_filmplane_width);
	up_bias *= (y_offset * m_filmplane_height);
	cray.m_direction = m_look;
	cray.m_direction *= m_filmplane_depth;
	cray.m_direction += right_bias;
	cray.m_direction += up_bias;
	cray.m_direction.normalize();

	// set origin of ray.
	cray.m_origin = m_position;
}
