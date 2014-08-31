#include <GLTools.h>
#include <GLShaderManager.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch SquareBatch;
GLShaderManager ShaderManager;
//the square
GLfloat SquareSize = 0.1f;
GLfloat Ver[]={ SquareSize,  SquareSize, 0.0f,
               -SquareSize,  SquareSize, 0.0f,
               -SquareSize, -SquareSize, 0.0f,
                SquareSize, -SquareSize, 0.0f};   
// the constant be needed in the following function
GLfloat stepsize = 0.01f; //step size automatically
GLfloat X = Ver[0]; //upper right x
GLfloat Y = Ver[7]; //lower left y
GLfloat keysize = 0.1f;  //step size when keyEvent

//will be called when created or changed the window size
void ChangeSize(int w, int h)
{
	glViewport(0,0,w,h);
}

//initialization before mainloop
void SetupRC()
{
	glClearColor(0.25f,0.25f,0.25f,1.0f);//background
	ShaderManager.InitializeStockShaders();  //initialize the shader 

	SquareBatch.Begin(GL_TRIANGLE_FAN, 4);  //batch
	SquareBatch.CopyVertexData3f(Ver);
	SquareBatch.End();
}
// move automatically
void MoveAutomatic(void)
{
	
	static GLfloat Xdirect = 1.0f;   //direct of move x
	static GLfloat Ydirect = 1.0f;   //direct of move y
	
	X += stepsize*Xdirect;
	Y += stepsize*Ydirect;
	//collision detection
	if(X > 1.0f) 
	{ 
		X = 1.0f; 
		Xdirect = -Xdirect; 
	}
	if(X < (-1.0f + 2*SquareSize) ) 
	{
		X = -1.0f+2*SquareSize; 
		Xdirect = -Xdirect;
	}
	if(Y < -1.0f)
	{
		Y = -1.0f;
		Ydirect = -Ydirect;
	}
	if(Y > (1.0f-2*SquareSize))
	{
		Y = 1.0f-2*SquareSize;
		Ydirect = -Ydirect;
	}
	//calculate new Square
	Ver[0] = X;            Ver[1] = Y+2*SquareSize;
	Ver[3] = X-2*SquareSize; Ver[4] = Y+2*SquareSize;
	Ver[6] = X-2*SquareSize; Ver[7] = Y;
	Ver[9] = X;            Ver[10] = Y;
	SquareBatch.CopyVertexData3f(Ver);
}
//KeyEvent
void SpecialKey(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_F1:
		X = SquareSize; Y = -SquareSize;
		break;
	case GLUT_KEY_UP:
		Y += keysize;
		break;
	case GLUT_KEY_DOWN:
		Y -= keysize;
		break;
	case GLUT_KEY_LEFT:
		X -= keysize;
		break;
	case GLUT_KEY_RIGHT:
		X += keysize;
		break;
	}
	//colision detection
	if(X > 1.0f)                    X = 1.0f; 
	if(X < (-1.0f + 2*SquareSize)) 	X = -1.0f+2*SquareSize; 
	if(Y < -1.0f)		            Y = -1.0f;
	if(Y > (1.0f-2*SquareSize))		Y = 1.0f-2*SquareSize;
	//calculate new square
	Ver[0] = X;            Ver[1] = Y+2*SquareSize;
	Ver[3] = X-2*SquareSize; Ver[4] = Y+2*SquareSize;
	Ver[6] = X-2*SquareSize; Ver[7] = Y;
	Ver[9] = X;            Ver[10] = Y;
	SquareBatch.CopyVertexData3f(Ver);
}
//Render Scene
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat vRed[]={0.75f, 0.75f, 0.75f, 1.0f}; //the color of square
	ShaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);  //Render square
	SquareBatch.Draw();     //draw square
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
		return 1; // Problem: glewInit failed, something is seriously wrong.
	}
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKey);

	SetupRC();

	glutMainLoop();
	return 0;
}