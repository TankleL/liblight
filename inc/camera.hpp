/* ****************************************************************************
camera.h
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
	class LIGHT_API Camera
			{
	public:
		Camera();
		virtual ~Camera();
	public:	// interface(s)
		/**
		@interface: generate_ray
		@param: x_offset means the logic x-position that the ray intersects with the film plane. range is [-0.5, 0.5]
		@param: y_offset means the logic y-position that the ray intersects with the film plane. range is [-0.5, 0.5]
		@return: a camera ray
		*/
		virtual void generate_ray(Math::Ray3& cray, Math::decimal x_offset, Math::decimal y_offset) = 0;
		
	public: // common method(s)

		void set_position(const Math::Point3& pos);
		void move_x(Math::decimal dist);
		void move_y(Math::decimal dist);
		void move_z(Math::decimal dist);

		void rotate_x(Math::decimal angle);
		void rotate_y(Math::decimal angle);
		void rotate_z(Math::decimal angle);

		// this method should be re-constructed in the future.
		void set_lens(Math::decimal width, Math::decimal height, Math::decimal depth);

		// get properties of camera.
		const Math::Point3& get_position() const;
		const Math::Vector3& get_right() const;
		const Math::Vector3& get_up() const;
		const Math::Vector3& get_look()	const;		

	protected:
		Math::Point3	m_position;
		Math::Vector3	m_up;
		Math::Vector3	m_right;
		Math::Vector3	m_look;
};

	inline Camera::Camera() :
		m_position(0.0f, 0.0f, 0.0f),
		m_right(1.0f, 0.0f, 0.0f),
		m_up(0.0f, 1.0f, 0.0f),
		m_look(0.0f, 0.0f, 1.0f)
	{}

	inline Camera::~Camera()
	{}

	inline void Camera::set_position(const Math::Point3& pos)
	{
		m_position = pos;
	}

	inline const Math::Point3& Camera::get_position() const
	{
		return m_position;
	}

	inline const Math::Vector3& Camera::get_right() const
	{
		return m_right;
	}

	inline const Math::Vector3& Camera::get_up() const
	{
		return m_up;
	}

	inline const Math::Vector3& Camera::get_look() const
	{
		return m_look;
	}

	inline void	Camera::move_z(Math::decimal dist)
	{
		m_position.m_x += m_look.m_x * dist;
		m_position.m_y += m_look.m_y * dist;
		m_position.m_z += m_look.m_z * dist;
	}

	inline void	Camera::move_x(Math::decimal dist)
	{
		m_position.m_x += m_right.m_x * dist;
		m_position.m_y += m_right.m_y * dist;
		m_position.m_z += m_right.m_z * dist;
	}

	inline void	Camera::move_y(Math::decimal dist)
	{
		m_position.m_x += m_up.m_x * dist;
		m_position.m_y += m_up.m_y * dist;
		m_position.m_z += m_up.m_z * dist;
	}

	inline void Camera::rotate_x(Math::decimal angle)
	{
		Math::Matrix4 rotation;
		Math::Matrix4Utils::rotate_axis(rotation, m_right, angle);

		m_up = rotation * m_up;
		m_look = rotation * m_look;
	}

	inline void Camera::rotate_y(Math::decimal angle)
	{
		Math::Matrix4 rotation;
		Math::Matrix4Utils::rotate_axis(rotation, m_up, angle);

		m_right = rotation * m_right;
		m_look = rotation * m_look;
	}

	inline void Camera::rotate_z(Math::decimal angle)
	{
		Math::Matrix4 rotation;
		Math::Matrix4Utils::rotate_axis(rotation, m_look, angle);

		m_right = rotation * m_right;
		m_up = rotation * m_up;
	}
}
