//Draw a square
//Make it rotate automatically around the z axis
#include <GLTools.h>
#include <GLShaderManager.h>
#include <math3d.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch SquareRotationBatch;
GLShaderManager shaderManager;
GLfloat SquareSize = 0.1f;
GLfloat Square[] = {SquareSize, SquareSize, 0.0f,
                   -SquareSize, SquareSize, 0.0f,
                   -SquareSize,-SquareSize, 0.0f,
                    SquareSize,-SquareSize, 0.0f};
static float Rot = 0.0f;   //the initialization of rotation
void SetupPC()
{
	glClearColor(0.75f, 0.75f, 0.75f,1.0f);
	shaderManager.InitializeStockShaders();
	
	SquareRotationBatch.Begin(GL_TRIANGLE_FAN, 4);
	SquareRotationBatch.CopyVertexData3f(Square);
	SquareRotationBatch.End();
}

void SceneShader()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat VColor[] = {0.25f,0.25f,0.25f,1.0f};

	M3DMatrix44f RotationMatrix;
	Rot += 1.0f; 

	//get the Rotation Matrix 
	//m3dDegToRad: translate angle to radian
	m3dRotationMatrix44(RotationMatrix, m3dDegToRad(Rot), 0.0f, 0.0f, 1.0f);  

	//use the flat shader
	shaderManager.UseStockShader(GLT_SHADER_FLAT, RotationMatrix ,VColor);

	SquareRotationBatch.Draw();

	// Swap buffers, and immediately refresh
	glutSwapBuffers();   
	glutPostRedisplay(); 
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