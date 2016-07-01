#ifndef  __Director_H_
#define  __Director_H_

#include "GLView.h"

class Director{
public:

	Director* getInstance();

	GLView* getGLView();

	void drawScene();
private:
	GLView* _glView;
};

#endif