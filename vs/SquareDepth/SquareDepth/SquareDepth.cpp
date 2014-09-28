//a square can rotate around the vector (1.0,1.0,1.0)
#include <GLTools.h>
#include <GLShaderManager.h>
#include <math3d.h>

#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif


GLBatch SquareBatch;
GLShaderManager ShaderManager;

GLFrame             viewFrame;
GLFrustum           viewFrustum;
GLMatrixStack       modelViewMatrix;
GLMatrixStack       projectionMatrix;
GLGeometryTransform transformPipeline;

//static GLfloat angle = 0.0f;  //initialize angle
void SetupRC()
{
	glEnable(GL_DEPTH_TEST);   //open depth test
	glClearColor(1.0f,1.0f,1.0f,1.0f);  //background: white
	ShaderManager.InitializeStockShaders();
	
	viewFrame.MoveForward(7.0f);
	
	GLfloat SquareSize = 0.1f;
	GLfloat Square[] = {SquareSize,  SquareSize, 0.0f,
		               -SquareSize,  SquareSize, 0.0f,
		               -SquareSize, -SquareSize, 0.0f,
		                SquareSize, -SquareSize, 0.0f};   //A square

	SquareBatch.Begin(GL_TRIANGLE_FAN, 4);
	SquareBatch.CopyVertexData3f(Square);
	SquareBatch.End();
}
void SceneShader()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
	modelViewMatrix.PushMatrix(viewFrame);

	GLfloat COLOR[] = {0.0f, 0.0f, 0.0f, 1.0f};  

	//M3DMatrix44f RotationMatrix;
	//angle += 1.0f;
	// rotation matrix
	// rotate around the vector (1.0,1.0,1.0)
	//m3dRotationMatrix44(RotationMatrix, m3dDegToRad(angle), 1.0f,1.0f,1.0f);

	ShaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), COLOR);
	SquareBatch.Draw();
	modelViewMatrix.PopMatrix();
	//swap buffers, and immediately refresh
	glutSwapBuffers();
	//glutPostRedisplay();
}
void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
}
void SpecialKey(int key ,int x, int y)
{
	if(key == GLUT_KEY_UP)
		viewFrame.RotateWorld(m3dDegToRad(-5.0),1.0f,0.0f,0.0f);
	if(key == GLUT_KEY_DOWN)
		viewFrame.RotateWorld(m3dDegToRad(5.0),1.0f,0.0f,0.0f);
	if(key == GLUT_KEY_LEFT)
		viewFrame.RotateWorld(m3dDegToRad(-5.0),0.0f,1.0f,0.0f);
	if(key == GLUT_KEY_RIGHT)
		viewFrame.RotateWorld(m3dDegToRad(5.0),0.0f,1.0f,0.0f);
	glutPostRedisplay();
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

	glutSpecialFunc(SpecialKey);

	SetupRC();
	glutMainLoop();
	return 0;
}