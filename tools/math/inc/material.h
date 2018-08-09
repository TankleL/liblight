/* ****************************************************************************
material.h
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


#if !defined(LIGHT_MATHINC_MATERIAL_H)
#define LIGHT_MATHINC_MATERIAL_H

#include "my-prerequisites.h"
#include "color.h"

namespace Light
{
	namespace Math
	{
		class Material
		{
		public:
			enum MaterialType : int
			{
				Unknown = 0,
				Phong
			};

		public:
			virtual MaterialType mtype() const = 0;
		};

		class PhongMaterial : public Material
		{
		public:
			PhongMaterial();
			PhongMaterial(const Color& ambient, const Color& diffuse,
				const Color& specular, const Color& emissive);
			virtual ~PhongMaterial();

		public:
			virtual MaterialType mtype() const override;

		public:
			Color m_ambient;
			Color m_diffuse;
			Color m_specular;
			Color m_emissive;
		};

		inline PhongMaterial::PhongMaterial()
		{}

		inline PhongMaterial::PhongMaterial(const Color& ambient, const Color& diffuse,
			const Color& specular, const Color& emissive)
			: m_ambient(ambient)
			, m_diffuse(diffuse)
			, m_specular(specular)
			, m_emissive(emissive)
		{}

		inline PhongMaterial::~PhongMaterial()
		{}

		inline Material::MaterialType PhongMaterial::mtype() const
		{ return Phong; }
	}
}

#endif