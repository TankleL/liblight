/* ****************************************************************************
@module simple scene reader
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
#include "scene-tile.hpp"
#include "material-default.hpp"
#include "rapidjson/document.h"

namespace Light
{

	/************************************************************************/
	/*                            DECLARATION                               */
	/************************************************************************/

	class SimpleReader
	{
	public:
		static bool parse_json(TileScene& out, const std::string& filename);
	};


	/************************************************************************/
	/*                            IMPLEMENTATION                            */
	/************************************************************************/

	inline bool SimpleReader::parse_json(TileScene& out, const std::string& filename)
	{
		std::ifstream input(filename);
		if (!input.is_open())
			return false;

		std::ostringstream oss;
		oss << input.rdbuf();
		std::string json_cnt = oss.str();

		rapidjson::Document doc;
		doc.Parse(json_cnt.c_str());

		if (doc.HasMember("mtrl_list") &&
			doc["mtrl_list"].IsArray())
		{
			for (auto& mtrl : doc["mtrl_list"].GetArray())
			{
				if (mtrl.HasMember("type") &&
					mtrl["type"].IsString() &&
					strcmp(mtrl["type"].GetString(), "default") == 0)
				{
					std::shared_ptr<DefaultMaterial> new_mtrl = std::make_shared<DefaultMaterial>();

					if (mtrl.HasMember("diffuse") && mtrl["diffuse"].IsArray())
					{
						rapidjson::Value jsClr = mtrl["diffuse"].GetArray();
						Math::Color clr(jsClr[0].GetDouble(), jsClr[1].GetDouble(), jsClr[2].GetDouble());
						new_mtrl->set_color(DefaultMaterial::DIFFUSE, clr);
					}

					if (mtrl.HasMember("emissive") && mtrl["emissive"].IsArray())
					{
						rapidjson::Value jsClr = mtrl["emissive"].GetArray();
						Math::Color clr(jsClr[0].GetDouble(), jsClr[1].GetDouble(), jsClr[2].GetDouble());
						new_mtrl->set_color(DefaultMaterial::EMISSIVE, clr);
					}

					if (mtrl.HasMember("specular") && mtrl["specular"].IsArray())
					{
						rapidjson::Value jsClr = mtrl["specular"].GetArray();
						Math::Color clr(jsClr[0].GetDouble(), jsClr[1].GetDouble(), jsClr[2].GetDouble());
						new_mtrl->set_color(DefaultMaterial::SPECULAR, clr);
					}

					if (mtrl.HasMember("refraction") && mtrl["refraction"].IsArray())
					{
						rapidjson::Value jsClr = mtrl["refraction"].GetArray();
						Math::Color clr(jsClr[0].GetDouble(), jsClr[1].GetDouble(), jsClr[2].GetDouble());
						new_mtrl->set_color(DefaultMaterial::REFRACT, clr);
					}

					if (mtrl.HasMember("IOR") && mtrl["IOR"].IsArray())
					{
						rapidjson::Value jsClr = mtrl["IOR"].GetArray();
						Math::Color clr(jsClr[0].GetDouble(), jsClr[1].GetDouble(), jsClr[2].GetDouble());
						new_mtrl->set_color(DefaultMaterial::IOR, clr);
					}

					if (mtrl.HasMember("name") && mtrl["name"].IsString())
					{
						out.add_material(mtrl["name"].GetString(), new_mtrl);
					}
				}
			}
		}

		if (doc.HasMember("shape_list") &&
			doc["shape_list"].IsArray())
		{
			for (auto& shape : doc["shape_list"].GetArray())
			{
				if (shape.HasMember("type") &&
					shape["type"].IsString())
				{
					if (strcmp(shape["type"].GetString(), "sphere") == 0)
					{
						rapidjson::Value jsPos = shape["pos"].GetArray();
						Math::Point3 pos(jsPos[0].GetDouble(), jsPos[1].GetDouble(), jsPos[2].GetDouble());

						Math::decimal radius = shape["radius"].GetDouble();
						std::string ref_mtrl = shape["mtrl"].GetString();

						out.add_shape(std::make_shared<Math::ShapeSphere>(pos, radius), ref_mtrl);
					}
					else if (strcmp(shape["type"].GetString(), "triangle") == 0)
					{
						rapidjson::Value jsPos = shape["pos"].GetArray();
						Math::Point3 v0(jsPos[0].GetDouble(), jsPos[1].GetDouble(), jsPos[2].GetDouble());
						Math::Point3 v1(jsPos[3].GetDouble(), jsPos[4].GetDouble(), jsPos[5].GetDouble());
						Math::Point3 v2(jsPos[6].GetDouble(), jsPos[7].GetDouble(), jsPos[8].GetDouble());

						std::string ref_mtrl = shape["mtrl"].GetString();

						out.add_shape(std::make_shared<Math::ShapeTriangle>(v0, v1, v2), ref_mtrl);
					}
					else if (strcmp(shape["type"].GetString(), "rectangle") == 0)
					{
						rapidjson::Value jsPos = shape["pos"].GetArray();
						Math::Point3 v0(jsPos[0].GetDouble(), jsPos[1].GetDouble(), jsPos[2].GetDouble());
						Math::Point3 v1(jsPos[3].GetDouble(), jsPos[4].GetDouble(), jsPos[5].GetDouble());
						Math::Point3 v2(jsPos[6].GetDouble(), jsPos[7].GetDouble(), jsPos[8].GetDouble());
						Math::Point3 v3(jsPos[9].GetDouble(), jsPos[10].GetDouble(), jsPos[11].GetDouble());

						std::string ref_mtrl = shape["mtrl"].GetString();

						out.add_shape(std::make_shared<Math::ShapeRectangle>(v0, v1, v2, v3), ref_mtrl);
					}
				}
			}
		}

		return true;
	}

}
