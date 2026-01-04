#pragma once

#include <glm/common.hpp>
#include "../lib/include/glad/glad.h"

#include <vector>
#include <cstddef>

#include "shader.h"
#include "texture.h"

using point = glm::vec<3, float>;

namespace b 
{
	class rectangle
	{
	private: 
		bool has_own_texture = false;
		point vertices[4];
		unsigned int VAO, EBO;
		texture tex;

		const unsigned int indices[6] = 
		{
			0, 1, 3,
			1, 2, 3
		};

		const float tex_coords[8] = 
		{
			1.0f, 1.0f, // top right
			1.0f, 0.0f, // bottom right
			0.0f, 0.0f, // bottom left
			0.0f, 1.0f  // top left
		};

	public: 
		//TODO que no reciba 4 vertices, sino un origen y unas dimensiones en pixeles
		rectangle(point _a, point _b, point _c, point _d)
		{ 
			unsigned int VBO_pos, VBO_tex;
			vertices[0] = _a;
			vertices[1] = _b;
			vertices[2] = _c;
			vertices[3] = _d;
			
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO_pos);
			glGenBuffers(1, &VBO_tex);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO_pos);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, VBO_tex);
			glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), &tex_coords, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void set_texture(const texture &_texture)
		{
			tex = _texture;
			has_own_texture = true;
		}

		void draw() 
		{
			if (has_own_texture) 
				tex.bind();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	};
}
