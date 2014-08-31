#include <GLTools.h>
#include <GLShaderManager.h>
#ifdef _APPLE_
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch SquareBatch;
GLShaderManager ShaderManager;
GLfloat SquareSize = 0.1f;
GLfloat Ver[]={ SquareSize,  SquareSize, 0.0f,
               -SquareSize,  SquareSize, 0.0f,
               -SquareSize, -SquareSize, 0.0f,
                SquareSize, -SquareSize, 0.0f};
void ChangeSize(int w, int h)
{
	glViewport(0,0,w,h);
}
void SetupRC()
{
	glClearColor(0.25f,0.25f,0.25f,1.0f);//background
	ShaderManager.InitializeStockShaders();

	SquareBatch.Begin(GL_TRIANGLE_FAN, 4);
	SquareBatch.CopyVertexData3f(Ver);
	SquareBatch.End();
}

void MoveAutomatic(void)
{
	GLfloat stepsize = 0.1f;
	static GLfloat Xdirect = 1.0f;
	static GLfloat Ydirect = 1.0f;
	GLfloat X = Ver[0];
	GLfloat Y = Ver[7];

	X += stepsize*Xdirect;
	Y += stepsize*Ydirect;

	if(X > 1.0f) 
	{ 
		X = 1.0f; 
		Xdirect = -Xdirect; 
	}
	if(X < (-1.0f + 2*stepsize) ) 
	{
		X = -1.0f+2*stepsize; 
		Xdirect = -Xdirect;
	}
	if(Y < -1.0f)
	{
		Y = -1.0f;
		Ydirect = -Ydirect;
	}
	if(Y > (1.0f-2*stepsize))
	{
		Y = 1.0f-2*stepsize;
		Ydirect = -Ydirect;
	}

	Ver[0] = X;            Ver[1] = Y+2*stepsize;
	Ver[3] = X-2*stepsize; Ver[4] = Y+2*stepsize;
	Ver[6] = X-2*stepsize; Ver[7] = Y;
	Ver[9] = X;            Ver[10] = Y;
	SquareBatch.CopyVertexData3f(Ver);
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat vRed[]={0.75f, 0.75f, 0.75f, 1.0f};
	ShaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	SquareBatch.Draw();
	glutSwapBuffers();     //Flush drawing commands
	MoveAutomatic();
	glutPostRedisplay();   //Redraw
}

int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutCreateWindow("aSquare_MoveAutomatic");

	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n",glewGetErrorString(err));
		return 1;
	}
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();

	glutMainLoop();
	return 0;
}