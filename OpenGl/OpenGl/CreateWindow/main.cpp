#include <stdlib.h>
#include "GLView.h"
#include "glfw3.h"

int main()
{
	
	GLView* glView = new GLView();
	if (glView->createWindow("OpenGL Lesson One"))
	{
		glView->render();
	}

	delete glView;
	glView = nullptr; 

	system("pause");
	return 1;
}