#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>
#include "render/GLProgram.h"
#include "render/CCTexture2D.h"
#include "render/Render.h"

class Sprite
{
public:
	static Sprite* create();
	static Sprite* createWithFileName(std::string filename);
	virtual bool init();
	virtual bool initWithFileName(std::string filename);

	void visit(Render* render);

	void setPosition(const Vec2& position);
	void setPosition(float x, float y);

	inline void setName(std::string name){ _name = name; }
	inline std::string getName(){ return _name; }

private:
	void initShaderProgram();

private:
	GLProgram m_glProgram;
	Texture2D texture2d;
	QuadCommand _quadCommand;
	Vec2 _position;
	std::string _name;
};

#endif