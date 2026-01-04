#pragma once

#include <algorithm>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

enum class camera_movement 
{
	forward, backward,
	left, right
};
	
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

namespace b
{
	class camera
	{
	public:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldup;

		//Camera angles
		float yaw;
		float pitch;
		//camera options
		float movement_speed;
		float mouse_sensitivity;
		float zoom;

		bool flat_plane_movement = false;

		camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f),
		       glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f),
		       float _yaw = YAW,
			   float _pitch = PITCH
		) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
		{
			position = _position;
			worldup = _up;
			yaw = _yaw;
			pitch = _pitch;
			update_camera_vectors();
		}

		camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float _yaw, float _pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
		{
			position = glm::vec3(posX, posY, posZ);
			worldup = glm::vec3(upX, upY, upZ);
			yaw = _yaw;
			pitch = _pitch;
			update_camera_vectors();
		}

		glm::mat4 get_view_matrix()
		{
			return glm::lookAt(position, position + front, up);
		}

		void process_keyboard(camera_movement direction, float delta_time)
		{
			glm::vec3 usable_front = front;
			float velocity = movement_speed * delta_time;
			if (flat_plane_movement)
			{
				glm::vec3 flat_front = front;
				flat_front.y = 0.0f;
				if (glm::length(flat_front) > 0.0f)
					flat_front = glm::normalize(flat_front);
				usable_front = flat_front;
			}

			if (direction == camera_movement::forward)
				position += usable_front * velocity;
			if (direction == camera_movement::backward)
				position -= usable_front * velocity;
			if (direction == camera_movement::left)
				position -= right * velocity;
			if (direction == camera_movement::right)
				position += right * velocity;
		}

		void process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch = true)
		{
			std::cout << "Se mueve el mouse!!" << std::endl;
			xoffset *= mouse_sensitivity;
			yoffset *= mouse_sensitivity;
			yaw   += xoffset;
			pitch += yoffset;
			if (constrain_pitch)
				pitch = std::clamp(pitch, -89.0f, 89.0f);

			update_camera_vectors();
		}

		void process_mouse_scroll(float yoffset)
		{
			zoom -= (float)yoffset;
			zoom = std::clamp(zoom, 1.0f, 45.0f);
		}

		void set_flat_plane_movement(bool state)
		{
			flat_plane_movement = state;
		}
		
	private:
		void update_camera_vectors()
		{
			glm::vec3 _front;
			_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			_front.y = sin(glm::radians(pitch));
			_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			front = glm::normalize(_front);
			right = glm::normalize(glm::cross(front, worldup));
			up = glm::normalize(glm::cross(right, front));
		}
	};

}
