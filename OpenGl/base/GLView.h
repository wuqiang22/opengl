#ifndef _GL_VIEW_H
#define _GL_VIEW_H
#include "GL/glew.h"
#include "glfw3.h"

#include <stdlib.h>
#include <string>

struct GLViewContentAtts{
	int redBits;
	int greenBits;
	int blueBits;
	int alphaBits;
	int depthBits;
	int stencilBits;
};




class GLView{
public:
	GLView();
	void onGLFWError(int errorID, const char* errorDesc);
	void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify);
	void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y);
	void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y);
	void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void onGLFWCharCallback(GLFWwindow* window, unsigned int character);
	void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y);
	void onGLFWframebuffersize(GLFWwindow* window, int w, int h);
	void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height);
	void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified);

	bool createWindow(std::string  windowname);
	void setViewContentAtts(GLViewContentAtts glContextAttrs);

	bool initGlew();
	void render();
	~GLView();
private:
	GLFWwindow* _mainWindow;
	GLViewContentAtts _glContextAttrs;
};

#endif