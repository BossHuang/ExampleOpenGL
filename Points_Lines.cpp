//Draw points and then use lines to make them connecting.
//You can use space to see all steps and the different function of drawing lines
//There are three function to draw different lines and one function to draw points.
//The points here is crrated randomly.
#include <GLTools.h>
#include <GLShaderManager.h>

#include <stdlib.h>    //rand()
#include <time.h>      //time()

#ifdef __APPLE__
#include <glut/glut.h>
#else 
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch pointsBatch;  
GLBatch linesBatch;
GLBatch linestripBatch;
GLBatch lineloopBatch;
GLShaderManager shaderManager;
const GLint pointNumber=6;   //points number
static int enterNumber = 0;  //control which Batch will be called
void ChaneSize(int w, int h)  //called when window is created at first or changed
{
	glViewport(0,0,w,h);
}
void SetupPC()
{
	glClearColor(1.0f,1.0f,1.0f,1.0f);  //background: white
	shaderManager.InitializeStockShaders();

	GLfloat pMatrix[pointNumber][3];    // points matrix

	GLfloat aRandom;
	srand((unsigned int)time(NULL));     //random seed and the current time is the seed
	for(int i = 0; i < pointNumber; i++)
	{
		aRandom = rand()/(GLfloat)RAND_MAX*2.0f-1.0f;   //create a random between -1 to 1
		pMatrix[i][0] = aRandom;//x
		aRandom = rand()/(GLfloat)RAND_MAX*2.0f-1.0f;
		pMatrix[i][1] = aRandom;//y
		pMatrix[i][2] = 0.0f;   //z
	}
	//Points
	pointsBatch.Begin(GL_POINTS, pointNumber);
	pointsBatch.CopyVertexData3f(pMatrix);
	pointsBatch.End();
	//Lines
	linesBatch.Begin(GL_LINES, pointNumber);
	linesBatch.CopyVertexData3f(pMatrix);
	linesBatch.End();
	//LineStrip
	linestripBatch.Begin(GL_LINE_STRIP, pointNumber);
	linestripBatch.CopyVertexData3f(pMatrix);
	linestripBatch.End();
	//LineLoop
	lineloopBatch.Begin(GL_LINE_LOOP, pointNumber);
	lineloopBatch.CopyVertexData3f(pMatrix);
	lineloopBatch.End();
}
void RenderScene()
{
	//clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat vRed[] = {0.0f, 0.0f, 0.0f, 1.0f};  //the color of points
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);

	switch(enterNumber)
	{
	case 0:
		glPointSize(3);
		pointsBatch.Draw();   //draw points
		break;
	case 1:
		linesBatch.Draw();    //draw Lines
		break;
	case 2:
		linestripBatch.Draw();  //draw LineStrip
		break;
	case 3:
		lineloopBatch.Draw();   //draw LineLoop
		break;
	}
	glutSwapBuffers();    //Flush drawing commands
}

//A normal ASCII key has been pressed.
//In this case, advance the scene when the space bar is pressed.
void KeyPressFunc(unsigned char key, int x, int y)
{
	if (key == 32)   //the ASCII of space is 32
		enterNumber = (enterNumber + 1) % 4;
	glutPostRedisplay();  //update content of windows
}

int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH |GLUT_STENCIL);

	glutInitWindowSize(800,600);
	glutCreateWindow("Points_Lines");

	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	glutReshapeFunc(ChaneSize);
	glutKeyboardFunc(KeyPressFunc);
	glutDisplayFunc(RenderScene);
	
	SetupPC();
	glutMainLoop();  //main loop
	return 0;
}

