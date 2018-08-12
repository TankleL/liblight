/*******************************************************************************
@module scene-tile
@remarks tile scene means that it is a scene without tree structure

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
#include "../inc/scene-tile.hpp"

using namespace Light;

TileScene::TileScene()
{}

TileScene::~TileScene()
{}

void TileScene::add_shape(const std::shared_ptr<Math::Shape>& shape)
{
	m_shapes.push_back(shape);
}

bool TileScene::hit_detect(HitInfo& info, const Math::Ray3& ray_in)
{
	bool retval = false;

	Math::Intersection inters;
	for (const auto& shape : m_shapes)
	{
		bool hit = shape->intersected(inters, ray_in);
		if (hit && !retval)
		{ // firtst hit
			retval = hit;
			info.inters = inters;
		}
		else if (hit)
		{ // hit other shape
			if (inters.m_travel < info.inters.m_travel)
			{ // use the nearest one
				info.inters = inters;
			}
		}
	}

	return retval;
}