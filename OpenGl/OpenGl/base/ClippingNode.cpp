#include "ClippingNode.h"
#include "CommonMacros.h"
#include "Director.h"
#include "render/GLProgram.h"

#include "render/ccShader_PositionTexture_uColor.vert"
#include "render/ccShader_PositionTexture_uColor.frag"


GLint ClippingNode::s_layer = -1;

ClippingNode::ClippingNode()
	:_inverted(false)
{

}

ClippingNode::~ClippingNode()
{

}


ClippingNode* ClippingNode::create()
{
	ClippingNode* node = new (std::nothrow) ClippingNode();
	if (!node->init())
	{
		CC_SAFE_DELETE(node);
	}
	return node;
}

ClippingNode* ClippingNode::create(Sprite* pStencil)
{
	ClippingNode* node = new (std::nothrow) ClippingNode();
	if (!node->init(pStencil))
	{
		CC_SAFE_DELETE(node);
	}
	return node;
}

bool ClippingNode::init()
{
	return init(nullptr);
}

bool ClippingNode::init(Sprite* pStencil)
{
	m_stencil = pStencil;
	return true;
}

void ClippingNode::setSprite(Sprite* pSelf)
{
	self = pSelf;
}

void ClippingNode::setStencil(Sprite* stencil)
{
	m_stencil = stencil;
}

void ClippingNode::onBeforeVisit()
{
	s_layer++;
	mask_layer = 1<<s_layer;

	_currentStencilEnabled = glIsEnabled(GL_STENCIL_TEST);
	glGetIntegerv(GL_STENCIL_WRITEMASK, (GLint *)&_currentStencilWriteMask);
	glGetIntegerv(GL_STENCIL_FUNC, (GLint *)&_currentStencilFunc);
	glGetIntegerv(GL_STENCIL_REF, &_currentStencilRef);
	glGetIntegerv(GL_STENCIL_VALUE_MASK, (GLint *)&_currentStencilValueMask);
	glGetIntegerv(GL_STENCIL_FAIL, (GLint *)&_currentStencilFail);
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, (GLint *)&_currentStencilPassDepthFail);
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, (GLint *)&_currentStencilPassDepthPass);

	glEnable(GL_STENCIL_TEST);

	glStencilMask(mask_layer);
	glGetBooleanv(GL_DEPTH_WRITEMASK, &_currentDepthWriteMask);

	glDepthMask(GL_FALSE);

	glStencilFunc(GL_NEVER, mask_layer, mask_layer);
	glStencilOp(!_inverted ? GL_ZERO : GL_REPLACE, GL_KEEP, GL_KEEP);

	drawFullScreenQuadClearStencil();

	glStencilFunc(GL_NEVER, mask_layer, mask_layer);
	glStencilOp(!_inverted ? GL_REPLACE : GL_ZERO, GL_KEEP, GL_KEEP);
}

void ClippingNode::drawFullScreenQuadClearStencil()
{
	Director* director = Director::getInstance();

	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

	Vec2 vertices[] = {
		Vec2(-1, -1),
		Vec2(1, -1),
		Vec2(1, 1),
		Vec2(-1, 1)
	};

	GLProgram* glProgram = new (std::nothrow) GLProgram();
	glProgram->initWithSource(ccPositionTexture_uColor_vert, ccPositionTexture_uColor_frag);
	int colorLocation = glProgram->getUniformLocation("u_color");

	Color4F color(1, 1, 1, 1);
	glUseProgram(glProgram->shaderProgram);
	glProgram->setUniformsForBuiltins();
	glUniformMatrix4fv(colorLocation, (GLsizei)1, GL_FALSE, &color.a);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void ClippingNode::onAfterVisit()
{
	// restore the depth test state
	glDepthMask(_currentDepthWriteMask);
	glStencilFunc(GL_EQUAL, mask_layer, mask_layer);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}

void ClippingNode::onAfterVisitStencil()
{
	glStencilFunc(_currentStencilFunc, _currentStencilRef, _currentStencilValueMask);
	glStencilOp(_currentStencilFail, _currentStencilPassDepthFail, _currentStencilPassDepthPass);
	glStencilMask(_currentStencilWriteMask);
	if (!_currentStencilEnabled)
	{
		glDisable(GL_STENCIL_TEST);
	}

	// we are done using this layer, decrement
	s_layer--;
}

void ClippingNode::visit(Render* render)
{
	onBeforeVisit();

	m_stencil->visit(render);

	onAfterVisitStencil(); 

	self->visit(render);
	onAfterVisit();
}