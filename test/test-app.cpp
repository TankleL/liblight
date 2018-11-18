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
	Math::Resolution resolution = Math::Resolution(200, 100);

	m_scene = new TileScene();
	m_renderer = new RdrrIterablePathTracing(resolution, 2);
	m_texture = new Texture2D(resolution);
	m_camera = new DefaultCamera(16, 9, 6);
	m_camera->move_z(-1.1);
	((RdrrIterablePathTracing*)m_renderer)->set_camera(m_camera);

	if (!SimpleReader::parse_json(*(TileScene*)m_scene, "../../test/data/cornell-box.json"))
	{
		return false;
	}

	return true;
}

void TestApp::draw()
{
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
		((RdrrIterablePathTracing*)m_renderer)->flush();
		break;
	}
}

