#pragma once

#include <glm/common.hpp>
#include "../lib/include/glad/glad.h"
#include "shader.h"

using point = glm::vec<3, float>;

namespace bru
{
	class triangle
	{
	private: 
		point vertices[3];
		unsigned int VBO, VAO;

	public: 
		triangle(point _a, point _b, point _c)
		{ 
			vertices[0] = _a;
			vertices[1] = _b;
			vertices[2] = _c;

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
					glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void draw() 
		{
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	};
}
