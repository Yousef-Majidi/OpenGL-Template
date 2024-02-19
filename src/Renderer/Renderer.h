#ifndef RENDERER_H
#define RENDERER_H

#include "../Shader/shaderinit.h"
#include <glad/glad.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	Shader getShader() const;
	void initializeGLFW();
	void initializeGLAD();
	void initializeShader(const char*, const char*);
	void render(const GLuint VAO, const GLuint EBO, const GLuint numVertices);

private:
	Shader m_shader{};
};
#endif // !RENDERER_H
