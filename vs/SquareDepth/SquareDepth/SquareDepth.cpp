
#include <GLTools.h>
#include <GLShaderManager.h>
#include <math3d.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif




void ChangeSize(int w, int h)
{
	glViewport(0,0,w,h);
}
int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800,600);
	glutCreateWindow("Square_Rotation");

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	} 
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(SceneShader);

	SetupPC();
	glutMainLoop();
	return 0;
}