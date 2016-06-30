#include "GLProgram.h"
#include <stdio.h>

// Attribute names
const char* GLProgram::ATTRIBUTE_NAME_COLOR = "a_color";
const char* GLProgram::ATTRIBUTE_NAME_POSITION = "a_position";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD = "a_texCoord";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD1 = "a_texCoord1";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD2 = "a_texCoord2";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD3 = "a_texCoord3";
const char* GLProgram::ATTRIBUTE_NAME_NORMAL = "a_normal";
const char* GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT = "a_blendWeight";
const char* GLProgram::ATTRIBUTE_NAME_BLEND_INDEX = "a_blendIndex";

bool GLProgram::compileShader(GLuint* shader, GLenum type, const GLchar* shaderSource)
{
	if (shaderSource == NULL)
	{
		return false;
	}
	*shader = glCreateShader(type);
	const GLchar *sources[] = {
		"uniform mat4 CC_PMatrix;\n"
		"uniform mat4 CC_MVMatrix;\n"
		"uniform mat4 CC_MVPMatrix;\n"
		"uniform mat3 CC_NormalMatrix;\n"
		"uniform vec4 CC_Time;\n"
		"uniform vec4 CC_SinTime;\n"
		"uniform vec4 CC_CosTime;\n"
		"uniform vec4 CC_Random01;\n"
		"uniform sampler2D CC_Texture0;\n"
		"uniform sampler2D CC_Texture1;\n"
		"uniform sampler2D CC_Texture2;\n"
		"uniform sampler2D CC_Texture3;\n"
		"//CC INCLUDES END\n\n",
		shaderSource,
	};
	glShaderSource(*shader, sizeof(sources)/sizeof(*sources), sources, NULL);
	glCompileShader(*shader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, infoLog);
		printf(infoLog);
		return false;
		//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return success == GL_TRUE;
}

void GLProgram::link()
{
	glAttachShader(this->shaderProgram,this->vertexShader);
	glAttachShader(this->shaderProgram, this->fragementShaer);

	glLinkProgram(this->shaderProgram);

	GLint success;
	GLchar infoLog[512];
	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	GLint num = 0;
	glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTES, &num);

	
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(this->vertexShader);
	glDeleteShader(this->fragementShaer);
}

void GLProgram::initWithSource(const char* vertexShaderSource, const char*  fragementShaderSource)
{
	this->shaderProgram = glCreateProgram();

	if (!compileShader(&this->vertexShader, GL_VERTEX_SHADER, (const GLchar*)vertexShaderSource))
	{
		return; 
	}
	
	if (!compileShader(&this->fragementShaer, GL_FRAGMENT_SHADER,(const GLchar*)fragementShaderSource))
	{
		return;
	}
	bindPredefinedVertexAttribs();
	link();
}

void GLProgram::use()
{
	glUseProgram(this->shaderProgram);
}

void GLProgram::bindPredefinedVertexAttribs()
{
	static const struct {
		const char *attributeName;
		int location;
	} attribute_locations[] =
	{
		{ GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION },
		{ GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR },
		{ GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD },
		{ GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1 },
		{ GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2 },
		{ GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3 },
		{ GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL },
	};

	const int size = sizeof(attribute_locations) / sizeof(attribute_locations[0]);

	for (int i = 0; i < size; i++) {
		glBindAttribLocation(this->shaderProgram, attribute_locations[i].location, attribute_locations[i].attributeName);
	}
}

void GLProgram::parseAttribute()
{
	_vertexAttribs.clear();
	GLint activeAttributes = 0;
	glGetProgramiv(this->shaderProgram, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
	
	if (activeAttributes > 0)
	{
		GLint maxLength;
		glGetProgramiv(this->shaderProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

		for (int i = 0; i < activeAttributes; i++)
		{
			VertexAttrib vertexAttrib;
			GLchar* attribName = (GLchar*)alloca(maxLength + 1);
			GLint length, size;
			GLenum type;
			glGetActiveAttrib(this->shaderProgram, i, maxLength, nullptr, &vertexAttrib.size, &vertexAttrib.type, attribName);
			std::string name = attribName;
			vertexAttrib.name = name;
			GLint position = glGetAttribLocation(this->shaderProgram, attribName);
			vertexAttrib.index = position;
			_vertexAttribs[vertexAttrib.name] = vertexAttrib;
		}
	}
}