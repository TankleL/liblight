/*******************************************************************************
@module rennderer-patht

@abbreviation patht ==> path tracing

@link path tracing reference - https://en.wikipedia.org/wiki/Path_tracing

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
#include "../tools/math/inc/mathinc.h"
#include "../inc/renderer-patht.hpp"
#include "../inc/material-default.hpp"

using namespace Light;

RdrrPathTracing::RdrrPathTracing(int max_radiance_depth)
	: m_max_radiance_depth(max_radiance_depth)
{}

void RdrrPathTracing::set_camera(std::shared_ptr<Camera> camera)
{
	m_camera = camera;
}

void RdrrPathTracing::render(Texture2D& output, const Scene& scene)
{
	Math::Resolution reso = output.get_resolution();


}

bool RdrrPathTracing::radiance(Math::Color& output, const Scene& scene, const Math::Ray3& ray_in, int depth)
{
	bool retval = false;
	bool quit = false;
	
	Scene::HitInfo hit_info;
	quit = !scene.hit_detect(hit_info, ray_in);

	if (!quit)
	{	
		if (depth > m_max_radiance_depth)
		{ // Russian Roulette
			// Stop the recursion randomly based on the surface reflectivity.
			// TODO: impl R.R.
			quit = true;
		}
		else
		{
			if ("default" == hit_info.mtrl->type())
			{
				const DefaultMaterial* mtrl = 
					static_cast<const DefaultMaterial*>(hit_info.mtrl);

				if (mtrl->has_property(DefaultMaterial::DIFFUSE))
				{

				}

				if (mtrl->has_property(DefaultMaterial::REFLECT))
				{

				}

				if (mtrl->has_property(DefaultMaterial::REFRACT))
				{
					
				}

				if (mtrl->has_property(DefaultMaterial::EMISSIVE))
				{

				}
			}
		}
	}

	return retval;
}
