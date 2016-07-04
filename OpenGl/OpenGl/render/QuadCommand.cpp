#include "QuadCommand.h"

QuadCommand::QuadCommand()
	:_quadsCount(0),
	_quads(NULL)
{

}

void QuadCommand::init(V3F_C4B_T2F_Quad* quads, size_t quadsCount, Texture2D texture2d, GLProgram _glProgram,const Mat4& _mv)
{
	_quads = quads;
	_quadsCount = quadsCount;
	_texture2d = texture2d;
	m_glProgram = _glProgram;
	mv = _mv;
}

QuadCommand::~QuadCommand()
{

}

void QuadCommand::useMaterial()
{
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, _texture2d.getName());

	glUniform1i(m_glProgram.texture2d0Pos, 0);

	m_glProgram.apply(mv);
}

