#include "../tools/math/inc/mathinc.h"
#include "../inc/renderer-patht.hpp"
#include "../inc/scene-tile.hpp"
#include "../inc/camera-default.hpp"
#include "../inc/material-default.hpp"
#include "../inc/img-util.hpp"

using namespace std;
using namespace Light;
using namespace Light::Math;

int main(int argc, char** argv)
{
	TileScene scn;
	RdrrPathTracing rdr(8);
	Texture2D rt(Math::Resolution(200, 200));

	shared_ptr<DefaultMaterial> mtrl_ball = make_shared<DefaultMaterial>();
	mtrl_ball->set_color(DefaultMaterial::DIFFUSE, Color(1, 1, 1));
	scn.add_material("mtrl_ball", mtrl_ball);

	shared_ptr<DefaultMaterial> mtrl_light_green = make_shared<DefaultMaterial>();
	mtrl_light_green->set_color(DefaultMaterial::EMISSIVE, Color(0.5, 1, 0.5));
	scn.add_material("mtrl_light_green", mtrl_light_green);

	shared_ptr<DefaultMaterial> mtrl_light_red = make_shared<DefaultMaterial>();
	mtrl_light_red->set_color(DefaultMaterial::EMISSIVE, Color(1, 0.5, 0.5));
	scn.add_material("mtrl_light_red", mtrl_light_red);

	scn.add_shape(std::make_shared<Math::ShapeSphere>(Math::Point3(0.0, 0.0, 5.0), 1), "mtrl_ball");
	scn.add_shape(std::make_shared<Math::ShapeSphere>(Math::Point3(5.0, 15.0, 0.0), 10), "mtrl_light_green");
	scn.add_shape(std::make_shared<Math::ShapeSphere>(Math::Point3(-5.0, 15.0, 0.0), 10), "mtrl_light_red");


	shared_ptr<DefaultCamera> cam = make_shared<DefaultCamera>(10.0, 10.0);
	rdr.set_camera(cam);

	rdr.render(rt, scn);

	ImgUtil::save_texture_as_ppm6("output.ppm", rt);

	return 0;
}