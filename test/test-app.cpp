#include "test-app.hpp"

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
	m_scene = new TileScene();
	m_renderer = new RdrrPathTracing(40, 2);
	m_texture = new Texture2D(Math::Resolution(200, 100));
	m_camera = new DefaultCamera(16, 9, 6);
	m_camera->move_z(-1.1);
	((RdrrPathTracing*)m_renderer)->set_camera(m_camera);

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
