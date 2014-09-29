//A Example to show how to use scissor
//there is no SetupRC in this example and all scissor is written in SceneRender.
#include <GLTools.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

void SceneRender()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);  //background color:red
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);  //clear the window with current color

	glScissor(100,100,600,400);  //scissor the window
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f); //color green
	
	glEnable(GL_SCISSOR_TEST);  //open scissor and it should be there
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	glScissor(50,50,200,200);  //scissor window again and it can cover the before scissor
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	glDisable(GL_SCISSOR_TEST);//close scissor
	glutSwapBuffers();
}
void ChangeSize(int w,int h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
}

int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH| GLUT_STENCIL);
	glutInitWindowSize(800,600);
	glutCreateWindow("Scissor");

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(SceneRender);
	                             
	glutMainLoop();
	return 0;
}