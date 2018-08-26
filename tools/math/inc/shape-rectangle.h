/* ****************************************************************************
shape-rectangle.h
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


#if !defined(LIGHT_MATHINC_SHAPE_RECTANGLE_H)
#define LIGHT_MATHINC_SHAPE_RECTANGLE_H

#include "my-prerequisites.h"
#include "shape-triangle.h"

namespace Light
{
	namespace Math
	{
		class ShapeRectangle : public Shape
		{
		public:
			ShapeRectangle(const Point3& vt0, const Point3& vt1,
				const Point3& vt2, const Point3& vt3);
			virtual ~ShapeRectangle();

		public:
			virtual bool intersected(Intersection& inters, const Ray3& ray_in) override;

		protected:
			ShapeTriangle*	m_tris[2];
		};

		inline ShapeRectangle::ShapeRectangle(const Point3& vt0, const Point3& vt1,
			const Point3& vt2, const Point3& vt3)
		{
			m_tris[0] = new ShapeTriangle(vt0, vt1, vt2);
			m_tris[1] = new ShapeTriangle(vt2, vt3, vt0);
		}

		inline ShapeRectangle::~ShapeRectangle()
		{
			delete m_tris[0];
			delete m_tris[1];
		}

		inline bool ShapeRectangle::intersected(Intersection& inters, const Ray3& ray_in)
		{
			bool res = false;

			if (m_tris[0]->intersected(inters, ray_in))
				res = true;
			else if (m_tris[1]->intersected(inters, ray_in))
				res = true;

			return res;
		}

	} // namespace Math
} // namespace Light


#endif // LIGHT_MATHINC_SHAPE_RECTANGLE_H