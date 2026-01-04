#include "../lib/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <unistd.h>

#include "shader.h"
#include "triangle.h"
#include "rectangle.h"
#include "cube.h"

constexpr float scr_w = 800;
constexpr float scr_h = 600;

glm::vec3 camera_pos =  glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up = glm::vec3(0.0f, 0.1, 0.0);

float yaw = -90.0f, pitch;
float last_x = 400, last_y = 300;
bool first_mouse = true;
float fov = 90.0f;

float delta_time = 0.0f;
float last_frame = 0.0f;

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
	glm::vec3 direction = camera_front;
	direction.y = 0.0f;

	if (glm::length((direction)) > 0.0f)
		direction = glm::normalize(direction);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	const float camera_speed = 2.5f * delta_time;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera_pos += camera_speed * direction;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera_pos -= camera_speed * direction;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
	}
	camera_pos.y = 0.0f;
}

void clear() 
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glfwMakeContextCurrent(window);

	check_error(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed To initialize GLAD");

	glViewport(0, 0, scr_w, scr_h);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
	{ 
		glViewport(0, 0, width, height); 
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
	{
		if (first_mouse)
		{
			last_x = xpos;
			last_y = ypos;
			first_mouse = false;
		}

		float xoffset = xpos - last_x;	
		float yoffset = last_y - ypos;	
		last_x = xpos;
		last_y = ypos;

		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		yaw += xoffset;
		pitch += yoffset;
		pitch = std::clamp(pitch, -89.0f, 89.0f);

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		camera_front = glm::normalize(direction);
	});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset){
		fov -= (float)yoffset;
		fov = std::clamp(fov, 1.0f, 45.0f);
	});


	glEnable(GL_DEPTH_TEST);

	//
	b::texture tex1("src/textures/container.jpg");
	b::texture tex2("src/textures/awesomeface.png");
	
	b::cube cubo;

	glm::vec3 cube_positions[] = 
	{
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	
	b::shader mi_shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
	mi_shader.use();
	mi_shader.set_int("texture1", 0);
	mi_shader.set_int("texture2", 1);

	while(!glfwWindowShouldClose(window))
	{
		float current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		process_input(window);
		clear();

		glActiveTexture(GL_TEXTURE0);
		tex1.bind();
		glActiveTexture(GL_TEXTURE1);
		tex2.bind();

		glm::mat4 proj(1.0f);


		proj = glm::perspective(glm::radians(fov), scr_w/scr_h, 0.1f, 100.0f);
		mi_shader.set_mat4("projection", proj);

		for (unsigned i = 0; i < 10; i++)
		{
			glm::mat4 model(1.0f); //Rotaciones, cosas que les hacemos a los objetos
			model = glm::translate(model, cube_positions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0, 0.3, 0.5));
			mi_shader.set_mat4("model", model);


			glm::mat4 view(1.0f);

			view = glm::lookAt(
				camera_pos, //Desde donde
				camera_pos + camera_front, // Hacia donde
				camera_up //Vector hacia arriba
			);

			mi_shader.set_mat4("view", view);

			cubo.draw();
		}

		display(window);
	}
	
	glfwTerminate();
	return 0;
}
