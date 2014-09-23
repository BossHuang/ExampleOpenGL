#include <GLTools.h>
#include <GLShaderManager.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLShaderManager shaderManager;
GLBatch PyramidBatch;
void SetupRC()
{
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	shaderManager.InitializeStockShaders();
	GLfloat PyramidButtonSize = 0.1f;
	GLfloat Pyramid[] = {PyramidButtonSize, PyramidButtonSize, 0.0f,
	                    -PyramidButtonSize, PyramidButtonSize, 0.0f,
	                    -PyramidButtonSize,-PyramidButtonSize, 0.0f,
	                     PyramidButtonSize,-PyramidButtonSize, 0.0f,
	                     0.0f,             0.0f,               0.1f};
	PyramidBatch.Begin(GL_TRIANGLE_STRIP, 5);
	PyramidBatch.CopyVertexData3f(Pyramid);
	PyramidBatch.End();
}
void SceneShader()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat VColor[] = {0.25f, 0.25f, 0.25f, 1.0f};
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY , VColor);
	PyramidBatch.Draw();
	glutSwapBuffers();
}
void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
}

int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800,600);
	glutCreateWindow("Pramid");

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "GLEW Error : %s\n", glewGetErrorString(err));
		return 1;
	}
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(SceneShader);

	SetupRC();
	glutMainLoop();

	return 0;
}