#pragma once

#include "../tools/math/inc/mathinc.h"
#include "../inc/renderer-patht.hpp"
#include "../inc/scene-tile.hpp"
#include "../inc/camera-default.hpp"
#include "../inc/material-default.hpp"
#include "../inc/img-util.hpp"
#include "../inc/tree.hpp"
#include "../inc/readers/reader-simple.hpp"


class TestApp
{
public:
	TestApp();
	virtual ~TestApp();

public:
	bool init();
	void draw();
	const Light::Texture2D* get_rt_texture();

protected:
	Light::Scene*		m_scene;
	Light::Renderer*	m_renderer;
	Light::Texture2D*	m_texture;
	Light::Camera*		m_camera;
};


