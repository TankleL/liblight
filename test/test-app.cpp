#include "test-app.hpp"


#include "../inc/scene-tile.hpp"
#include "../inc/camera-default.hpp"
#include "../inc/material-default.hpp"
#include "../inc/img-util.hpp"
#include "../inc/tree.hpp"
#include "../inc/readers/reader-simple.hpp"
#include "../inc/renderer-patht.hpp"
#include "../inc/renderer-patht-iterable.hpp"

using namespace std;
using namespace Light;
using namespace Light::Math;

TestApp::TestApp()
	: m_scene(nullptr)
	, m_renderer(nullptr)
	, m_texture(nullptr)
	, m_camera(nullptr)
	, m_is_dirty(true)
{}

TestApp::~TestApp()
{
	safe_delete(m_scene);
	safe_delete(m_renderer);
	safe_delete(m_texture);
	safe_delete(m_camera);
}

bool TestApp::init()
{
	Math::Resolution resolution = Math::Resolution(300, 150);

	m_scene = new TileScene();
	m_renderer = new RdrrIterablePathTracing(resolution, 5);
	m_texture = new Texture2D(resolution);
	m_camera = new DefaultCamera(16, 9, 6);
	m_camera->move_x(0.2f);
	m_camera->move_z(-2.0f);
	m_camera->move_y(-0.8f);
	((RdrrIterablePathTracing*)m_renderer)->set_camera(m_camera);

	const char* test_files[] = {
		"../../test/data/cornell-box.json",
		"../../test/data/light-up.json",
		"../../test/data/glass-spheres.json"
	};

	if (!SimpleReader::parse_json(*(TileScene*)m_scene, test_files[2]))
	{
		return false;
	}

	return true;
}

void TestApp::draw()
{
	if (m_is_dirty)
	{
		((RdrrIterablePathTracing*)m_renderer)->flush();
		m_is_dirty = false;
	}

	m_renderer->render(*m_texture, *m_scene);
}

const Texture2D* TestApp::get_rt_texture()
{
	return m_texture;
}

void TestApp::on_press_key_alphabet(char letter)
{
	switch (letter)
	{
	case 'f':
		m_is_dirty = true;
		break;

	case 'w':
		m_camera->move_z(0.2f);
		m_is_dirty = true;
		break;

	case 's':
		m_camera->move_z(-0.2f);
		m_is_dirty = true;
		break;

	case 'a':
		m_camera->move_x(-0.2f);
		m_is_dirty = true;
		break;

	case 'd':
		m_camera->move_x(0.2f);
		m_is_dirty = true;
		break;

	case 'e':
		m_camera->move_y(0.2f);
		m_is_dirty = true;
		break;

	case 'c':
		m_camera->move_y(-0.2f);
		m_is_dirty = true;
		break;
	}
}

