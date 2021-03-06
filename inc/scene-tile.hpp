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

#pragma once

#include "node.hpp"
#include "scene.hpp"
#include "../tools/math/inc/mathinc.h"

namespace Light
{
	class LIGHT_API TileScene : public Scene
	{
	public:
		TileScene();
		virtual ~TileScene();

	public:
		virtual bool hit_detect(HitInfo& info, const Math::Ray3& ray_in) const override;

	public:
		void add_material(const std::string& material_name, const std::shared_ptr<Material>& material);
		void add_shape(const std::shared_ptr<Math::Shape>& shape, const std::string& material_name);

	protected:
		struct _ShapeStoreItem
		{
			_ShapeStoreItem(const std::shared_ptr<Math::Shape>& the_shape,
				const std::string& the_material_name)
				: shape(the_shape)
				, material_name(the_material_name)
			{}

			std::shared_ptr<Math::Shape>		shape;
			std::string							material_name;
		};

	protected:
		std::vector<_ShapeStoreItem>								m_shapes;
		std::unordered_map<std::string, std::shared_ptr<Material>>	m_materials;
	};
}
