#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <sys/inotify.h>

#include <iostream>
#include <unistd.h>

#include "shader.h"
#include "triangle.h"
#include "rectangle.h"

constexpr int scr_w = 800;
constexpr int scr_h = 600;

constexpr unsigned BUF_LEN = (1024 * (sizeof(struct inotify_event) + 16));


void check_error(bool condition, std::string message) 
{
	if (condition)
	{
		std::cerr << message << std::endl;
		glfwTerminate();
		exit(-1);
	}
}

void process_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void clear() 
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void display(GLFWwindow* window)
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow * window = glfwCreateWindow(scr_w, scr_h, "Reaprendiendo", NULL, NULL);
	check_error(window == NULL, "Failed to create GLFW window");
	
	glfwMakeContextCurrent(window);

	check_error(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed To initialize GLAD");

	glViewport(0, 0, scr_w, scr_h);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
	{ 
		glViewport(0, 0, width, height); 
	});

	rectangle rect = 
	{
		{ 0.5f,  0.5f, 0.0f},
		{ 0.5f, -0.5f, 0.0f},
		{-0.5f, -0.5f, 0.0f},
		{-0.5f,  0.5f, 0.0f} 
	};

	shader mi_shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

	while(!glfwWindowShouldClose(window))
	{
		process_input(window);
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			mi_shader.compile();
		}
		clear();

		mi_shader.use();
		rect.draw();

		display(window);
	}
	
	glfwTerminate();
	return 0;
}
