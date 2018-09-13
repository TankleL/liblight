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
		RdrrPathTracing(int sample_scale = 8,
			int max_radiance_depth = 8);

	public:
		virtual void render(Texture2D& output, const Scene& scene) override;

	public:
		void set_camera(std::shared_ptr<Camera> camera);

	protected:
		Math::Color _radiance(const Scene& scene, const Math::Ray3& ray_in, int depth);
		Math::Ray3 _random_ray(const Math::Vector3& normal, const Math::Point3& hit_pos) const;
		Math::Ray3 _reflect_ray(const Math::Ray3& ray_in, const Math::Point3& hit_point, const Math::Vector3& normal) const;

	protected:
		std::shared_ptr<Camera>	m_camera;
		int	m_max_radiance_depth;
		int m_sample_scale;

	protected:
		Math::Color m_back_clr;
		Math::Color	m_cur_ior;		// current IOR - Index of Refraction
	};
}
