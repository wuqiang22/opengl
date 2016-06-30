#ifndef  __QUAD_COMMAND_H_
#define __QUAD_COMMAND_H_

#include "ccTypes.h"

class QuadCommand{
public:
	QuadCommand();
	~QuadCommand();

	void init(V3F_C4B_T2F_Quad* quads, size_t quadsCount);

	inline V3F_C4B_T2F_Quad* getQuads() const { return _quads; }
	inline ssize_t getQuadCount() const { return _quadsCount; }
private:
	size_t _quadsCount;
	V3F_C4B_T2F_Quad* _quads;
};

#endif