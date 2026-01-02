#include <glm/common.hpp>
#include <glad/glad.h>
#include "shader.h"

using point = glm::vec<3, float>;

class rectangle
{
private: 
	point vertices[4];
	unsigned int VBO, VAO, EBO;

	const unsigned int indices[6] = 
	{
		0, 1, 3,
		1, 2, 3
	};
public: 
	rectangle(point _a, point _b, point _c, point _d)
	{ 
		vertices[0] = _a;
        vertices[1] = _b;
        vertices[2] = _c;
        vertices[3] = _d;
		
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void draw() 
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
};
