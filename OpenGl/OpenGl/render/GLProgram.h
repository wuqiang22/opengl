#ifndef  __GL_PROGRAM_H_
#define __GL_PROGRAM_H_

#include "GL/glew.h"
#include "glfw3.h"
#include <string>
#include <unordered_map>

struct VertexAttrib
{
	GLuint index;
	GLint size;
	GLenum type;
	std::string name;
};

class GLProgram{
public:
	enum
	{
		VERTEX_ATTRIB_POSITION,
		VERTEX_ATTRIB_COLOR,
		VERTEX_ATTRIB_TEX_COORD,
		VERTEX_ATTRIB_TEX_COORD1,
		VERTEX_ATTRIB_TEX_COORD2,
		VERTEX_ATTRIB_TEX_COORD3,
		VERTEX_ATTRIB_NORMAL,
		VERTEX_ATTRIB_BLEND_WEIGHT,
		VERTEX_ATTRIB_BLEND_INDEX,
		VERTEX_ATTRIB_MAX,

		// backward compatibility
		VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
	};

	// Attribute names
	static const char* ATTRIBUTE_NAME_COLOR;
	static const char* ATTRIBUTE_NAME_POSITION;
	static const char* ATTRIBUTE_NAME_TEX_COORD;
	static const char* ATTRIBUTE_NAME_TEX_COORD1;
	static const char* ATTRIBUTE_NAME_TEX_COORD2;
	static const char* ATTRIBUTE_NAME_TEX_COORD3;
	static const char* ATTRIBUTE_NAME_NORMAL;
	static const char* ATTRIBUTE_NAME_BLEND_WEIGHT;
	static const char* ATTRIBUTE_NAME_BLEND_INDEX;
public:
	void initWithSource(const char* vertexShaderSource, const char* fragementShaderSource);
	bool compileShader(GLuint* shader, GLenum type, const GLchar* shaderSource);
	void link();
	void use();
	void bindPredefinedVertexAttribs();

	void parseAttribute();
private:
	GLuint shaderProgram,vertexShader,fragementShaer;

	std::unordered_map<std::string, VertexAttrib> _vertexAttribs;
};

#endif