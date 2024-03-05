#ifndef APP_H
#define APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "../Renderer/Renderer.h"
#include "../Shapes/Shape.h"

class App
{
public:
	App() {};
	App(unsigned int, unsigned int, const char*, const char*);
	~App();
	void run();
	void addShape(Shape* shape);

private:
	const char* m_vertexShaderPath = nullptr;
	const char* m_fragmentShaderPath = nullptr;
	GLFWwindow* m_window{};
	std::vector<Shape*> m_shapes{};
	std::unique_ptr<Renderer> m_renderer;

	void createWindow(unsigned int, unsigned int);
	void initializesShapes();
	void gameLoop();
	void render();

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif // !App_H