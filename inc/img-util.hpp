/*******************************************************************************
@module image utilities

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

#include "prerequisites.hpp"
#include "exceptions/msg-exception.hpp"
#include "texture2d.hpp"

namespace Light
{
	namespace ImgUtil
	{
		inline void save_texture_as_ppm6(const std::string& file_path, const Texture2D& tex)
		{
			BEGIN_TRY();
			std::ofstream bmp_file(file_path, std::ios::binary);
			if (false == bmp_file.is_open())
				throw msg_exception("cannot open the file for outputting bmp data");

			// form the header
			std::ostringstream oss;
			oss << "P6" << std::endl;
			oss << tex.get_resolution().get_width() << " "
				<< tex.get_resolution().get_height() << std::endl;
			oss << "255" << std::endl;

			bmp_file << oss.str();

			// output image data
			const Math::Resolution res_tex = tex.get_resolution();
			for (int y = 1; y <= res_tex.get_height(); ++y)
			{
				for (int x = 0; x < res_tex.get_width(); ++x)
				{
					Math::Color	clr = tex.get_pixel(x, res_tex.get_height() - y);
					unsigned char r = static_cast<unsigned char>(clr.m_r * 255.0f);
					unsigned char g = static_cast<unsigned char>(clr.m_g * 255.0f);
					unsigned char b = static_cast<unsigned char>(clr.m_b * 255.0f);

					bmp_file << r << g << b;
				}
			}
			CTA();
		}
	}
}
