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

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"attribute vec3 position;\n"
"attribute vec4 m_color;\n"
"out vec4 v_fragmentColor;\n"
"void main()\n"
"{\n"
"v_fragmentColor = m_color;\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 tt;\n"
"in vec4 v_fragmentColor;\n"
"void main()\n"
"{\n"
"tt= v_fragmentColor;\n"
"}\n\0";


void GLView::initShaderProgram()
{
	// Build and compile our shader program
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		//std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindAttribLocation(shaderProgram, 0, "position");
	glBindAttribLocation(shaderProgram, 1, "m_color");

	glLinkProgram(shaderProgram);
	
	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	GLint num = 0;
	glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTES, &num);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	this->shaderProgram = shaderProgram;
}

void GLView::render()
{
	initShaderProgram();
	GLint activeAttributes = 0;
	glGetProgramiv(this->shaderProgram, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
	printf("use active attributes %i \n", activeAttributes);

	if (activeAttributes > 0)
	{
		GLint length, size;
		GLenum type;
		glGetProgramiv(this->shaderProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
		GLchar* attribName = (GLchar*)alloca(length + 1);
		glGetActiveAttrib(this->shaderProgram, 0, length, nullptr, &size, &type, attribName);
		

		GLint position =glGetAttribLocation(this->shaderProgram, attribName);
		printf("active attributes name = %s position = %i\n", attribName,position);

		attribName = (GLchar*)alloca(length + 1);
		glGetActiveAttrib(this->shaderProgram, 1, length, nullptr, &size, &type, attribName);
		position = glGetAttribLocation(this->shaderProgram, attribName);
		printf("active attributes name = %s position = %i\n", attribName, position);

	}
	

	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,1.0f, 0.5f, 0.2f, 1.0f,// Top Right
		0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.2f, 1.0f,// Bottom Right
		-0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.2f, 1.0f,// Bottom Left
		-0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 0.2f, 1.0f,// Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint bufferVbo;
	glGenBuffers(1, &bufferVbo);
	glBindBuffer(GL_ARRAY_BUFFER, bufferVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(0+3*sizeof(GLfloat)));

	GLuint bufferEbo;
	glGenBuffers(1, &bufferEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(_mainWindow))
	{
		/*
		GLfloat vertices[] = {
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.0f,
		};
		
		glBindBuffer(GL_ARRAY_BUFFER, bufferVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLES, 0, 3);*/

		glClearColor(0.2, 0.2, 0.2, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(this->shaderProgram);

		glBindVertexArray(vao);
		
		//GL_UNSIGNED_SHORT
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		
		glBindVertexArray(0);

		/* Swap front and back buffers */
		glfwSwapBuffers(_mainWindow);

		/* Poll for and process events */
		glfwPollEvents();

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