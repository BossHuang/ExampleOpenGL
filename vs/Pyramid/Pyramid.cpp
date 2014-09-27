//Draw a pyramid by three triangles and can automatically rotate around (1,0,0), the outline be draw also using red
//Undone--the pyramid can should be rotate manually around any directions.
//Undone--the pyramid be draw by 12 points now, but actually 4 points is what I only want to use
#include <GLTools.h>
#include <GLShaderManager.h>
#include <math3d.h>
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
	glEnable(GL_DEPTH_TEST);//open depth text
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);  //background color
	shaderManager.InitializeStockShaders();
	//Pyramid
	GLfloat PyramidButtonSize = 0.1f;
	GLfloat Pyramid[] = {0.1f, 0.0f, 0.1f,
	                     0.2f, 0.0f, 0.0f,
	                     0.0f, 0.1f, 0.0f,

						 0.1f, 0.0f, 0.1f,
						 0.2f, 0.0f, 0.0f,
						 0.0f, -0.1f, 0.0f,

						 0.1f, 0.0f, 0.1f,
						 0.0f,-0.1f, 0.0f,
						 0.0f, 0.1f, 0.0f,

						 0.0f,-0.1f, 0.0f,
						 0.2f, 0.0f, 0.0f,
						 0.0f, 0.1f, 0.0f,
	};
	PyramidBatch.Begin(GL_TRIANGLES, 12);
	PyramidBatch.CopyVertexData3f(Pyramid);
	PyramidBatch.End();

}

void SceneShader()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat VColor[] = {0.0f, 1.0f, 0.0f, 1.0f}; //the color of triangle
	GLfloat VvColor[] = {1.0f, 0.0f, 0.0f, 1.0f};  //the color of outline
	static GLfloat Rot = 0.0f;  //rotatiopn angle initialize
	M3DMatrix44f RotationMatrix;
	Rot += 5.0f;
	m3dRotationMatrix44(RotationMatrix, m3dDegToRad(Rot), 1.0f,0.0f,0.0f);
	shaderManager.UseStockShader(GLT_SHADER_FLAT , RotationMatrix, VColor);
	PyramidBatch.Draw();
	
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.0f, -1.0f);  //draw  outline
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glLineWidth(2.5f);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, RotationMatrix, VvColor);
	PyramidBatch.Draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glutSwapBuffers();
	glutPostRedisplay();
}
/*
void SpecialKey(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
	{
		m3dRotationMatrix44(RotationMatrix, m3dDegToRad(5.0f), 1.0f,0.0f,0.0f);
	}
	if(key == GLUT_KEY_DOWN)
	{
		m3dRotationMatrix44(RotationMatrix, m3dDegToRad(-5.0f), 1.0f,0.0f,0.0f);
	}
	if(key == GLUT_KEY_LEFT)
	{
		m3dRotationMatrix44(RotationMatrix, m3dDegToRad(5.0f), 0.0f,1.0f,0.0f);
	}
	if(key == GLUT_KEY_RIGHT)
	{
		m3dRotationMatrix44(RotationMatrix, m3dDegToRad(-5.0f), 0.0f,1.0f,0.0f);
	}
	glutPostRedisplay();
}
*/

/*
void Keyboard()
{

}
*/


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
//	glutSpecialFunc(SpecialKey);
//	glutKeyboardFunc(Keyboard);

	SetupRC();
	glutMainLoop();
	return 0;
}