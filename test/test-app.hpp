#pragma once

#include "../tools/math/inc/mathinc.h"
#include "../inc/scene.hpp"
#include "../inc/renderer.hpp"
#include "../inc/texture2d.hpp"
#include "../inc/camera.hpp"


class TestApp
{
public:
	TestApp();
	virtual ~TestApp();

public:
	bool init();
	void draw();
	const Light::Texture2D* get_rt_texture();

public:
	void on_press_key_alphabet(char letter);

protected:
	Light::Scene*		m_scene;
	Light::Renderer*	m_renderer;
	Light::Texture2D*	m_texture;
	Light::Camera*		m_camera;
};


