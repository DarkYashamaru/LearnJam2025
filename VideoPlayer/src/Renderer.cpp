#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

const char* GetGLErrorName(GLenum error) {
    switch (error) {
    case GL_NO_ERROR: return "GL_NO_ERROR";
    case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
    case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
    case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
    case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
    default: return "Unknown GL error";
    }
}

void GLCheckError()
{
    while (GLenum error = glGetError())
    {
        Debug::LogError("GL Error: " + std::string(GetGLErrorName(error)));
    }
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
{
    shader.Bind();
    //shader.SetUniform4f("u_color", 0.2f, 0.3f, 1.0f, 1.0f);

    vertexArray.Bind();
    indexBuffer.Bind();

    GLClearError();
    glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
    GLCheckError();
}
