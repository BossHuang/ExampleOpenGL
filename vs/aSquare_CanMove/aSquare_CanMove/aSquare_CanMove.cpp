//a square can be move by arrow key moments
#include <GLTools.h>
#include <GLShaderManager.h>
#ifdef _APPLE_
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif


GLBatch SquareBatch;
GLShaderManager shaderManager;

//square
GLfloat squareSize=0.1f;
GLfloat Ver[]={-squareSize, -squareSize, 0.0f,
	            squareSize, -squareSize, 0.0f,
	            squareSize, squareSize, 0.0f,
	           -squareSize, squareSize, 0.0f};    

void SetupRC()
{
	//background
	glClearColor(0.25f, 0.25f,0.25f,1.0f);

	shaderManager.InitializeStockShaders();

	SquareBatch.Begin(GL_TRIANGLE_FAN,4);
	SquareBatch.CopyVertexData3f(Ver);
	SquareBatch.End();
}


void SpecialKeys(int key, int x, int y)
{
	GLfloat stepsize=0.25f;
	GLfloat SquareX=Ver[0];
	GLfloat SquareY=Ver[7];

	switch(key)
	{
	case GLUT_KEY_UP: 
		SquareY += stepsize;
		break;
	case GLUT_KEY_DOWN:
		SquareY -= stepsize;
		break;
	case GLUT_KEY_LEFT:
		SquareX -= stepsize;
		break;
	case GLUT_KEY_RIGHT:
		SquareX += stepsize;
		break;
	}
	//collision detection
	if(SquareX < -1.0f)                  SquareX = -1.0f;
	if(SquareX > (1.0f - 2*squareSize))  SquareX = 1.0f - 2*squareSize;
	if(SquareY > 1.0f )                  SquareY = 1.0f;
	if(SquareY < (-1.0f + 2*squareSize)) SquareY = -1.0f + 2*squareSize;
	//new square after moved
	Ver[0]=SquareX;                      Ver[1]=SquareY-2*squareSize;
	Ver[3]=SquareX+2*squareSize;         Ver[4]=SquareY-2*squareSize;
	Ver[6]=SquareX+2*squareSize;         Ver[7]=SquareY;
	Ver[9]=SquareX;                      Ver[10]=SquareY;
	SquareBatch.CopyVertexData3f(Ver);
	glutPostRedisplay();  //update the windows
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat vRed[]={0.75f, 0.75f, 0.75f, 1.0f};
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	SquareBatch.Draw();
	
	glutSwapBuffers();
}

void ChangeSize(int w, int h)
{
	glViewport(0,0,w,h);
}

int main(int argc, char* argv[])
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