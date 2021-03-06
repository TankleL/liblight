/*******************************************************************************
@module material-default

==----------------------------------------------------------------------------==

MIT License

Copyright (c) 2018 Tankle L.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

#pragma once

#include "material.hpp"
#include "../tools/math/inc/mathinc.h"

namespace Light
{
	class LIGHT_API DefaultMaterial : public Material
	{
	public:
		enum MATERIAL_BIT
		{
			NONE = 0,
			DIFFUSE = 1,
			SPECULAR = 2,
			REFRACT = 4,
			EMISSIVE = 8,
			IOR = 16,			// Index of Refraction
		};

	public:
		DefaultMaterial();
		virtual ~DefaultMaterial();

	public:
		void set_color(MATERIAL_BIT bit, const Math::Color& clr);
		const Math::Color& get_color(MATERIAL_BIT bit) const;
		bool has_property(MATERIAL_BIT bit) const;

	protected:
		int				m_properties;
		Math::Color		m_color[6];
	};
}
