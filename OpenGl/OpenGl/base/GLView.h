#ifndef _GL_VIEW_H
#define _GL_VIEW_H
#include "GL/glew.h"
#include "glfw3.h"
#include "render/GLProgram.h"
#include "render/Render.h"
#include "CCImage.h"

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

extern CC_DLL const GLchar * ccPositionTextureColor_noMVP_frag;
extern CC_DLL const GLchar * ccPositionTextureColor_noMVP_vert;


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
	void initShaderProgram();
	void initRender();

	void render();

	void initTexture2d();

	~GLView();
private:
	GLFWwindow* _mainWindow;
	GLViewContentAtts _glContextAttrs;
	
	GLProgram m_glProgram;
	GLuint m_shaderProgram;
	Render m_render;

	Texture2D texture2d;
	
};

#endif