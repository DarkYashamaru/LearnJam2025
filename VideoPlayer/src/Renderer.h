#pragma once
#include <GL/glew.h>
#include "Debug.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

void GLClearError();

const char* GetGLErrorName(GLenum error);

void GLCheckError();

class Renderer
{
private:
public:
	void Clear() const;
	void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
};
