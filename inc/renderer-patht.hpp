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

#include "prerequisites.hpp"
#include "scene.hpp"
#include "renderer.hpp"
#include "camera.hpp"

namespace Light
{
	class LIGHT_API RdrrPathTracing : public Renderer
	{
	public:
		RdrrPathTracing(int max_radiance_depth = 8);

	public:
		virtual void render(Texture2D& output, const Scene& scene) override;

	public:
		void set_camera(std::shared_ptr<Camera> camera);

	protected:
		bool radiance(Math::Color& output, const Scene& scene, const Math::Ray3& ray_in, int depth);

	protected:
		std::shared_ptr<Camera>	m_camera;
		int	m_max_radiance_depth;
	};
}
