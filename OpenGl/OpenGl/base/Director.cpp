#include "Director.h"


Director*  Director::getInstance()
{
	static Director instance;
	return &instance;
}

GLView* Director::getGLView()
{
	return _glView;
}

void Director::drawScene()
{

}