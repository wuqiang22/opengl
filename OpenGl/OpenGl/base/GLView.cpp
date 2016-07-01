#include "GLView.h"
#include "render/QuadCommand.h"


#define STRINGIFY(A)  #A

#include "render/ccShader_PositionTextureColor_noMVP.frag"
#include "render/ccShader_PositionTextureColor_noMVP.vert"

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
	
	_frameSize.setSize(960, 640);
	_mainWindow = glfwCreateWindow(_frameSize.width, _frameSize.height, windowname.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(_mainWindow);  //在我们使用 GL 命令之前我们需要将创建的窗口设置为当前窗口

	//glViewport(0, 0, 480, 320);
	
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
/*
// Shaders
const char* vertexShaderSource = 
"attribute vec3 a_position;\n"
"attribute vec4 a_color;\n"
"out vec4 v_fragmentColor;\n"
"void main()\n"
"{\n"
"v_fragmentColor = a_color;\n"
"gl_Position = vec4(a_position.x, a_position.y, a_position.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = 
"out vec4 tt;\n"
"in vec4 v_fragmentColor;\n"
"void main()\n"
"{\n"
"tt= v_fragmentColor;\n"
"}\n\0";
*/

/*
const char* ccFilterShader_test_vert = "													\n\
attribute vec4 a_position;							\n\
attribute vec2 a_texCoord;							\n\
attribute vec4 a_color;								\n\
													\n\
#ifdef GL_ES										\n\
varying lowp vec4 v_fragmentColor;					\n\
varying mediump vec2 v_texCoord;					\n\
#else												\n\
varying vec4 v_fragmentColor;						\n\
varying vec2 v_texCoord;							\n\
#endif												\n\
													\n\
void main()											\n\
{													\n\
    gl_Position = a_position;		\n\
	v_fragmentColor = a_color;						\n\
}													\n\
";
const char* ccFilterShader_test_frag = 
"varying vec4 v_fragmentColor;\n\
\n\
void main() {\n\
gl_FragColor = v_fragmentColor;\n\
}";*/

/*
const char* ccPositionTextureColor_noMVP_vert =
"attribute vec4 a_position;\n"
"attribute vec2 a_texCoord;\n"
"attribute vec4 a_color;\n"

"#ifdef GL_ES\n"
"varying lowp vec4 v_fragmentColor;\n"
"varying mediump vec2 v_texCoord;\n"
"#else\n"
"varying vec4 v_fragmentColor;\n"
"varying vec2 v_texCoord;\n"
"#endif\n"

"void main()\n"
"{\n"
"gl_Position = a_position;\n"
"v_fragmentColor = a_color;\n"
"}\n\0";

const char* ccPositionTextureColor_noMVP_frag =
"#ifdef GL_ES\n"
"precision lowp float;\n"
"#endif\n"

"varying vec4 v_fragmentColor;\n"
"varying vec2 v_texCoord;\n"

"void main()\n"
"{\n"
"gl_FragColor = v_fragmentColor;\n"
"}\n\0";
*/



void GLView::initShaderProgram()
{
	this->m_glProgram.initWithSource(ccPositionTextureColor_noMVP_vert, ccPositionTextureColor_noMVP_frag);
	if (true)
	{		
		return;
	}
	/*
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

	glBindAttribLocation(shaderProgram, 0, "a_position");
	glBindAttribLocation(shaderProgram, 1, "a_color");

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

	this->m_shaderProgram = shaderProgram;
	*/
}


void GLView::initTexture2d()
{
	Image image;
	image.initWithImageFile("E://3.jpg");
	texture2d.initWithImage(&image);
}

void GLView::initRender()
{
	m_render.init();
}

void GLView::render()
{
	initRender();
	initShaderProgram();
	initTexture2d();
	/*
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
	glBindVertexArray(0);*/

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

	//glUseProgram(this->shaderProgram);

		this->m_glProgram.use();


		//glBindVertexArray(vao);
		
		//GL_UNSIGNED_SHORT
	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		QuadCommand command;
		V3F_C4B_T2F_Quad quads;

		quads.bl.colors = Color4B::WHITE;
		quads.br.colors = Color4B::WHITE;
		quads.tl.colors = Color4B::WHITE;
		quads.tr.colors = Color4B::WHITE;

		float atlasWidth = (float)texture2d.getPixelsWide();
		float atlasHeight = (float)texture2d.getPixelsHigh();

		Rect rect(0, 0, atlasWidth, atlasHeight);
		float x1 = -0.2;
		float y1 = -1;
		float x2 = x1 + 0.847;
		float y2 = y1 + 1;

		quads.bl.vertices = Vec3(x1, y1, 0);
		quads.br.vertices = Vec3(x2, y1, 0);
		quads.tl.vertices = Vec3(x1, y2, 0);
		quads.tr.vertices = Vec3(x2, y2, 0);

		

		float left, right, top, bottom;

		left = rect.origin.x / atlasWidth;
		right = (rect.origin.x + rect.size.width) / atlasWidth;
		top = rect.origin.y / atlasHeight;
		bottom = (rect.origin.y + rect.size.height) / atlasHeight;

		quads.bl.texCoords.u = left;
		quads.bl.texCoords.v = bottom;
		quads.br.texCoords.u = right;
		quads.br.texCoords.v = bottom;
		quads.tl.texCoords.u = left;
		quads.tl.texCoords.v = top;
		quads.tr.texCoords.u = right;
		quads.tr.texCoords.v = top;

		command.init(&quads, 1);
		m_render.putQuadCmd(&command);

		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, texture2d.getName());

		glUniform1i(m_glProgram.texture2d0Pos, 0);

		m_render.draw();

		
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

void GLView::setDesignResolution(size_t width, size_t height)
{
	_designResolutionSize.setSize(width, height);
}

Size GLView::getDesignResolution()
{
	return _designResolutionSize;
}

GLView::~GLView()
{
	glfwTerminate();
}