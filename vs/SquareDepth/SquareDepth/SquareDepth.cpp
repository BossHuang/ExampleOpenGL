//a square can rotate around the vector (1.0,1.0,1.0)
#include <GLTools.h>
#include <GLShaderManager.h>
#include <math3d.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif


GLBatch SquareBatch;
GLShaderManager ShaderManager;
GLfloat SquareSize = 0.1f;
GLfloat Square[] = {SquareSize,  SquareSize, 0.0f,
                   -SquareSize,  SquareSize, 0.0f,
                   -SquareSize, -SquareSize, 0.0f,
                    SquareSize, -SquareSize, 0.0f};   //A square
static GLfloat angle = 0.0f;  //initialize angle
void SetupRC()
{
	glEnable(GL_DEPTH_TEST);   //open depth test
	glClearColor(1.0f,1.0f,1.0f,1.0f);  //background: white
	ShaderManager.InitializeStockShaders();
	SquareBatch.Begin(GL_TRIANGLE_FAN, 4);
	SquareBatch.CopyVertexData3f(Square);
	SquareBatch.End();
}
void SceneShader()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat COLOR[] = {0.0f, 0.0f, 0.0f, 1.0f};  

	M3DMatrix44f RotationMatrix;
	angle += 1.0f;
	// rotation matrix
	// rotate around the vector (1.0,1.0,1.0)
	m3dRotationMatrix44(RotationMatrix, m3dDegToRad(angle), 1.0f,1.0f,1.0f);

	ShaderManager.UseStockShader(GLT_SHADER_FLAT, RotationMatrix, COLOR);
	SquareBatch.Draw();
	//swap buffers, and immediately refresh
	glutSwapBuffers();
	glutPostRedisplay();
}
void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
}
int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800,600);
	glutCreateWindow("SquareDepth");

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