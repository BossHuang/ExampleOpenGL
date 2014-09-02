#include <GLTools.h>
#include <GLShaderManager.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else 
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

int main(int argc, char* argv)
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

	glutInitWindowSize(1000,1000);
	glutCreateWindow("Square_CanMove");

	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys); // listen keyboard

	SetupRC();

	glutMainLoop();
	return 0;
}

