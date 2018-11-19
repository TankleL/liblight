/*******************************************************************************
@module rennderer-patht-iterable

@abbreviation patht ==> path tracing

@link path tracing reference - https://en.wikipedia.org/wiki/Path_tracing

@dependence renderer-patht

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
#include "renderer-patht-iterable.hpp"

using namespace Light;
using namespace Light::Math;

RdrrIterablePathTracing::RdrrIterablePathTracing(
	const Math::Resolution& resolution,
	int max_radiance_depth /* = 8 */)
	: RdrrPathTracing(1, max_radiance_depth)
	, m_rt_buffer(nullptr)
	, m_resolution(resolution)
	, m_iterate(0)
{
	m_rt_buffer = new Color[resolution.get_width() * resolution.get_height()];
}

RdrrIterablePathTracing::~RdrrIterablePathTracing()
{
	safe_delete(m_rt_buffer);
}

void RdrrIterablePathTracing::render(Texture2D& output, const Scene& scene)
{
	using namespace RdrrPathTracingUtil;

	assert(output.get_resolution() == m_resolution);

	const decimal rw = (decimal)m_resolution.get_width();
	const decimal rh = (decimal)m_resolution.get_height();
	const decimal h_rw = rw * 0.5;
	const decimal h_rh = rh * 0.5;

	++m_iterate;

	Ray3 cray(Point3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f));
	for (int y = 0; y < (int)rh; ++y)
	{
#pragma omp parallel for schedule(dynamic, 1) private(cray)
		for (int x = 0; x < (int)rw; ++x)
		{
			Color pixel;
			const decimal px = ((decimal)x - h_rw + pixel_turbulent(2)) / rw;
			const decimal py = ((decimal)y - h_rh + pixel_turbulent(2)) / rh;

			m_camera->generate_ray(cray, px, py);
			pixel = _radiance(scene, cray, 0);

			if(m_iterate - 1 > 0)
			{
				const Color& old = _get_pixel(x, y);
				pixel = old - (old / (decimal)m_iterate) + (pixel / (decimal)m_iterate);
				
				_write_pixel(x, y, pixel);

				pixel.clamp();
				output.set_pixel(x, y, pixel);
			}
			else
			{
				output.set_pixel(x, y, pixel);
				_write_pixel(x, y, pixel);
			}
		}
	}
}

void RdrrIterablePathTracing::flush()
{
	m_iterate = 0;
}

void RdrrIterablePathTracing::_write_pixel(int x, int y, const Math::Color& pixel)
{
	m_rt_buffer[x + y * m_resolution.get_width()] = pixel;
}

const Math::Color& RdrrIterablePathTracing::_get_pixel(int x, int y) const
{
	return m_rt_buffer[x + y * m_resolution.get_width()];
}


