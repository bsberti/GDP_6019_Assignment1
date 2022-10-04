#pragma once

#include "GL.h"

namespace gdp
{
	class Model {
	public:
		Model(const char* filepath);
		~Model();

		GLuint Vbo;
		GLuint VertexBufferId;
		GLuint IndexBufferId;

		unsigned int NumTriangles;
	};
}