#include "QuadCommand.h"

QuadCommand::QuadCommand()
	:_quadsCount(0),
	_quads(NULL)
{

}

void QuadCommand::init(V3F_C4B_T2F_Quad* quads, size_t quadsCount)
{
	_quads = quads;
	_quadsCount = quadsCount;
}

QuadCommand::~QuadCommand()
{

}