#include "GLView.h"

class GLFWEventHandler
{
public:
	static void onGLFWError(int errorID, const char* errorDesc)
	{
		if (_view)
			_view->onGLFWError(errorID, errorDesc);
	}

	static void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
	{
		if (_view)
			_view->onGLFWMouseCallBack(window, button, action, modify);
	}

	static void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
	{
		if (_view)
			_view->onGLFWMouseMoveCallBack(window, x, y);
	}

	static void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y)
	{
		if (_view)
			_view->onGLFWMouseScrollCallback(window, x, y);
	}

	static void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (_view)
			_view->onGLFWKeyCallback(window, key, scancode, action, mods);
	}

	static void onGLFWCharCallback(GLFWwindow* window, unsigned int character)
	{
		if (_view)
			_view->onGLFWCharCallback(window, character);
	}

	static void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y)
	{
		if (_view)
			_view->onGLFWWindowPosCallback(windows, x, y);
	}

	static void onGLFWframebuffersize(GLFWwindow* window, int w, int h)
	{
		if (_view)
			_view->onGLFWframebuffersize(window, w, h);
	}

	static void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height)
	{
		if (_view)
			_view->onGLFWWindowSizeFunCallback(window, width, height);
	}

	static void setGLViewImpl(GLView* view)
	{
		_view = view;
	}

	static void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
	{
		if (_view)
		{
			_view->onGLFWWindowIconifyCallback(window, iconified);
		}
	}

private:
	static GLView* _view;
};


GLView* GLFWEventHandler::_view = nullptr;

GLView::GLView()
{
	GLFWEventHandler::setGLViewImpl(this);
}

void GLView::onGLFWCharCallback(GLFWwindow* window, unsigned int character)
{

}

void GLView::onGLFWError(int errorID, const char* errorDesc)
{

}

void GLView::onGLFWframebuffersize(GLFWwindow* window, int w, int h)
{

}

void GLView::onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void GLView::onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
{

}

void GLView::onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
{

}

void GLView::onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y)
{

}

void GLView::onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
{

}

void GLView::onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y)
{

}

void GLView::onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height)
{

}

void GLView::setViewContentAtts(GLViewContentAtts glContextAttrs)
{

}

bool GLView::createWindow(std::string windowname)
{

	if (!glfwInit())
	{
		return false;
	}
	GLViewContentAtts _glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_RED_BITS, _glContextAttrs.redBits);
	glfwWindowHint(GLFW_GREEN_BITS, _glContextAttrs.greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, _glContextAttrs.blueBits);
	glfwWindowHint(GLFW_ALPHA_BITS, _glContextAttrs.alphaBits);
	glfwWindowHint(GLFW_DEPTH_BITS, _glContextAttrs.depthBits);
	glfwWindowHint(GLFW_STENCIL_BITS, _glContextAttrs.stencilBits);
	
	_mainWindow = glfwCreateWindow(960, 640, windowname.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(_mainWindow);  //在我们使用 GL 命令之前我们需要将创建的窗口设置为当前窗口

	glViewport(0, 0, 480, 320);
	
	glfwSetMouseButtonCallback(_mainWindow, GLFWEventHandler::onGLFWMouseCallBack);
	glfwSetCursorPosCallback(_mainWindow, GLFWEventHandler::onGLFWMouseMoveCallBack);
	glfwSetScrollCallback(_mainWindow, GLFWEventHandler::onGLFWMouseScrollCallback);
	glfwSetCharCallback(_mainWindow, GLFWEventHandler::onGLFWCharCallback);
	glfwSetKeyCallback(_mainWindow, GLFWEventHandler::onGLFWKeyCallback);
	glfwSetWindowPosCallback(_mainWindow, GLFWEventHandler::onGLFWWindowPosCallback);
	glfwSetFramebufferSizeCallback(_mainWindow, GLFWEventHandler::onGLFWframebuffersize);
	glfwSetWindowSizeCallback(_mainWindow, GLFWEventHandler::onGLFWWindowSizeFunCallback);
	glfwSetWindowIconifyCallback(_mainWindow, GLFWEventHandler::onGLFWWindowIconifyCallback);
	
	initGlew();
	return true;
}

void GLView::render()
{
	GLuint bufferVbo;
	glGenBuffers(1, &bufferVbo);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(_mainWindow))
	{
		
		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		
		glBindBuffer(GL_ARRAY_BUFFER, bufferVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(_mainWindow);

		/* Poll for and process events */
		glfwPollEvents();
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

bool GLView::initGlew()
{
	GLenum ret = glewInit();
	if (ret != GLEW_OK)
	{
		return false;
	}
	return true;
}

GLView::~GLView()
{
	glfwTerminate();
}