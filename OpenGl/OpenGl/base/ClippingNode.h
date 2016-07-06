#ifndef _CLIPPING_NODE_H_
#define _CLIPPING_NODE_H_

#include "GL/glew.h"
#include "glfw3.h"
#include "Sprite.h"

class ClippingNode{
public:

	ClippingNode();
	~ClippingNode();
	static GLint  s_layer;

	static ClippingNode* create();
	static ClippingNode* create(Sprite* pStencil);
	bool init();
	bool init(Sprite* pStencil);

	void onBeforeVisit();
	void onAfterVisitStencil();
	void onAfterVisit();

	void setSprite(Sprite* pSelf);
	void setStencil(Sprite* stencil);

	void drawFullScreenQuadClearStencil();

	void visit(Render* render);

private:
	Sprite* self;
	Sprite* m_stencil;
	
	GLint mask_layer;
	bool _inverted;

	GLboolean _currentStencilEnabled;
	GLuint _currentStencilWriteMask;
	GLenum _currentStencilFunc;
	GLint _currentStencilRef;
	GLuint _currentStencilValueMask;
	GLenum _currentStencilFail;
	GLenum _currentStencilPassDepthFail;
	GLenum _currentStencilPassDepthPass;
	GLboolean _currentDepthWriteMask;

	GLboolean _currentAlphaTestEnabled;
	GLenum _currentAlphaTestFunc;
	GLclampf _currentAlphaTestRef;
};

#endif