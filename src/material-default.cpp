/*******************************************************************************
@module  material-default

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

#include "api-dev-mod.hpp"
#include "../inc/material-default.hpp"
#include "../tools/math/inc/mathinc.h"

using namespace Light;

DefaultMaterial::DefaultMaterial()
	: Material("default")
	, m_properties(NONE)
{}

DefaultMaterial::~DefaultMaterial()
{}

void DefaultMaterial::set_color(MATERIAL_BIT bit, const Math::Color& clr)
{
	if (bit > 1)
		m_color[Math::fast_log2(bit)] = clr;
	else
		m_color[0] = clr;

	m_properties &= bit;
}

const Math::Color& DefaultMaterial::get_color(MATERIAL_BIT bit) const
{
	if (bit > 1)
		return m_color[Math::fast_log2(bit)];
	else
		return m_color[0];
}

bool DefaultMaterial::has_property(MATERIAL_BIT bit) const
{
	return m_properties & bit > 0;
}
