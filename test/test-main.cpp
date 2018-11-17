#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "test-app.hpp"

#include "../tools/glfw/deps/glad/glad.h"
#include "../tools/glfw/include/GLFW/glfw3.h"


using namespace std;
using namespace Light;
using namespace Light::Math;

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static GLuint gen_sprite_program();
static GLuint gen_rt_texture();
static void update_rt_texture(GLuint tex, const Light::Texture2D* src_tex);
static void main_loop(GLuint sprite_program, GLuint rt_texture, TestApp& test_app);


int main(int argc, char** argv)
{
	const int reso_width = 800;
	const int reso_height = 400;

	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* wnd = glfwCreateWindow(reso_width, reso_height, "Test Liblight", nullptr, nullptr);
	if(!wnd)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(wnd, key_callback);

	glfwMakeContextCurrent(wnd);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	
	const char* version = (const char *)glGetString(GL_VERSION);
	cout << "GL-Version: " << version << endl;

	glEnable(GL_TEXTURE_2D);
	GLuint sprite_program = gen_sprite_program();
	GLuint rt_texture = gen_rt_texture();
	TestApp test_app;
	if (!test_app.init())
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	int fb_width;
	int fb_height;
	while (!glfwWindowShouldClose(wnd))
	{
		glfwGetFramebufferSize(wnd, &fb_width, &fb_height);
		glViewport(0, 0, fb_width, fb_height);
		glClear(GL_COLOR_BUFFER_BIT);

		main_loop(sprite_program, rt_texture, test_app);

		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}

	glfwTerminate();


	return 0;
}

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static GLuint gen_sprite_program()
{
	// Quad Vertices
	static const struct
	{
		float x, y;
		float u, v;
	} vertices[4] =
	{
		//  x     y        u    v
		{ -1.f, -1.f,     0.f, 0.f },
		{ -1.f,  1.f,     0.f, 1.f },
		{  1.f,  1.f,     1.f, 1.f },
		{  1.f, -1.f,     1.f, 0.f }
	};

	// Vertex Buffer
	GLuint vb;
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Vertex Shader
	ifstream infile("../../test/shader/sprite_vs.glsl");
	if (!infile.is_open())
		return -1;
	stringstream ss_vs;
	ss_vs << infile.rdbuf();
	string vs_str = ss_vs.str();
	const char* vs_text = vs_str.c_str();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vs_text, nullptr);
	glCompileShader(vs);
	infile.close();

	// Fregment Shader (Pixel Shader)
	infile.open("../../test/shader/sprite_fs.glsl");
	if (!infile.is_open())
		return -2;
	stringstream ss_fs;
	ss_fs << infile.rdbuf();
	string fs_str = ss_fs.str();
	const char* fs_text = fs_str.c_str();
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fs_text, nullptr);
	glCompileShader(fs);
	infile.close();

	// Sprite Program
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	GLint loc_apos = glGetAttribLocation(program, "aPos");
	GLint loc_atexcoord = glGetAttribLocation(program, "aTexCoord");

	glEnableVertexAttribArray(loc_apos);
	glVertexAttribPointer(loc_apos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*) 0);

	glEnableVertexAttribArray(loc_atexcoord);
	glVertexAttribPointer(loc_atexcoord, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float)*2));

	return program;
}

static GLuint gen_rt_texture()
{
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return tex;
}

static void update_rt_texture(GLuint tex, const Light::Texture2D* src_tex)
{
	Light::Math::Resolution reso = src_tex->get_resolution();

	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, reso.get_width(), reso.get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, src_tex->get_buffer());
}

static void main_loop(GLuint sprite_program, GLuint rt_texture, TestApp& test_app)
{
	glUseProgram(sprite_program);
	
	test_app.draw();
	update_rt_texture(rt_texture, test_app.get_rt_texture());
	glBindTexture(GL_TEXTURE_2D, rt_texture);
	glDrawArrays(GL_QUADS, 0, 4);
}

