# liblight
a simple library to light up 3D scenes

![sample-img](./sample-imgs/readme-sample-img.jpg)

## 1. How to build
Please use cmake to build liblight out-of-source.

	cd liblight
	mkdir _build && cd _build
	cmake ..
	make


## 2. How to use
		
**test/test-main.cpp**:

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


**test/data/cornell-box.json**:

	{
		  "mtrl_list" :
		[
			{
				  "type" : "default"
				, "name" : "white_obj"
				, "diffuse" : [0.8, 0.8, 0.8]
			}
			,{
				  "type" : "default"
				, "name" : "blue_obj"
				, "diffuse" : [0.2, 0.3, 1]
			}
			,{
				  "type" : "default"
				, "name" : "green_obj"
				, "diffuse" : [0.2, 1, 0.4]
			}
			,{
				  "type" : "default"
				, "name" : "white_light"
				, "emissive" : [16, 16, 16]
			}
			,{
				  "type" : "default"
				, "name" : "refrac_ball"
				, "refraction" : [1, 1, 1]
				, "IOR" : [1.7, 1, 1]
			}
			,{
				  "type" : "default"
				, "name" : "mirror_ball"
				, "diffuse" : [0.4, 0.4, 0.4]
				, "specular" : [0.6, 0.6, 0.6]
			}
		]
		, "shape_list" :
		[
			{
				  "type" : "sphere"
				, "mtrl" : "white_light"
				, "radius" : 5
				, "pos" : [0, 6.6, 2.5]
				, "_comment" : "light"
			}
			,{
				  "type" : "rectangle"
				, "mtrl" : "white_obj"
				, "pos" : [
					-2, 1.7, -10,
					 2, 1.7, -10,
					 2, 1.7, 4,
					-2, 1.7, 4
					 ]
				, "_comment" : "box-top"
			}
			,{
				  "type" : "rectangle"
				, "mtrl" : "white_obj"
				, "pos" : [
					-2, -1.8, -10,
					-2, -1.8, 4,
					 2, -1.8, 4,
					 2, -1.8, -10]
				, "_comment" : "box-bottom"
			}
			,{
				  "type" : "rectangle"
				, "mtrl" : "green_obj"
				, "pos" : [
					2, -1.8, -10,
					2, -1.8, 4,
					2,  1.7, 4,
					2,  1.7, -10]
				, "_comment" : "box-right"
			}
			,{
				  "type" : "rectangle"
				, "mtrl" : "blue_obj"
				, "pos" : [
					-2, -1.8, -10,
					-2,  1.7, -10,
					-2,  1.7, 4,
					-2, -1.8, 4]
				, "_comment" : "box-left"
			}
			,{
				  "type" : "rectangle"
				, "mtrl" : "white_obj"
				, "pos" : [
					-2, -1.8, 4,
					-2,  1.7, 4,
					 2,  1.7, 4,
					 2, -1.8, 4]
				, "_comment" : "box-back"
			}
			,{
				  "type" : "rectangle"
				, "mtrl" : "white_obj"
				, "pos" : [
					-2, -1.8, -10,
					 2, -1.8, -10,
					 2,  1.7, -10,
					-2,  1.7, -10]
				, "_comment" : "box-front"
			}
			,{
				  "type" : "sphere"
				, "mtrl" : "refrac_ball"
				, "radius" : 0.5
				, "pos" : [0.8, -1.3, 2]
				, "_comment" : "refract-sphere"
			}
			,{
				  "type" : "sphere"
				, "mtrl" : "mirror_ball"
				, "radius" : 0.5
				, "pos" : [-0.8, -1.3, 2]
				, "_comment" : "mirror-sphere"
			}
		]
	}

## 3. Unsupported But Coming Soon Features

- Fresnel-Refraction
- Box-Shape
- Scene Node Management
- Scene Node Transform
- Cascading Scene
- K-D Tree
- Octree
- Depth of Field
- Rich Materials
