#include "../tools/math/inc/mathinc.h"
#include "../inc/renderer-patht.hpp"
#include "../inc/scene-tile.hpp"
#include "../inc/camera-default.hpp"
#include "../inc/material-default.hpp"
#include "../inc/img-util.hpp"
#include "../inc/tree.hpp"
#include "../inc/readers/reader-simple.hpp"

using namespace std;
using namespace Light;
using namespace Light::Math;

int main(int argc, char** argv)
{
	TileScene scn;
	RdrrPathTracing rdr(2000, 5);
	Texture2D rt(Math::Resolution(640, 360));

	shared_ptr<DefaultCamera> cam = make_shared<DefaultCamera>(16, 9, 6);
	cam->move_z(-1.1);
	rdr.set_camera(cam);

	if (SimpleReader::parse_json(scn, "../../test/data/cornell-box.json"))
	{
		const int frame_count = 1;
		for (int i = 0; i < frame_count; ++i)
		{
			rdr.render(rt, scn);
			std::ostringstream oss;
			oss << "output-" << i << ".ppm";
			ImgUtil::save_texture_as_ppm6(oss.str(), rt);

			cam->move_z(0.1);
		}
	}

	return 0;
}