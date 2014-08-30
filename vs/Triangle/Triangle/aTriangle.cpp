
//import library file 
#include <GLTools.h>           //OpenGL toolkit
#include <GLShaderManager.h>    //Shader Manager
//import platform file
#ifdef _APPLE_
#include <glut.h>   //OS
#else
#define FREEGLUT_STATIC   //windows
#include <GL/glut.h>
#endif

GLBatch triangleBatch;
GLShaderManager  shaderManager;  

void ChangeSize(int w, int h)   //just be created or change window size, this will be called
{
	glViewport(0,0,w,h);
}

void SetupRC()   //预加载纹理、建立几何图形、渲染器等操作
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);   //background

	//initialize the ShaderManager
	shaderManager.InitializeStockShaders();

	//a triangle
	GLfloat vVer[]={-0.5f, 0.0f, 0.0f,
		             0.0f, 0.5f, 0.0f,
		             0.5f, 0.0f, 0.0f};
	//batch shader triangle
	triangleBatch.Begin(GL_TRIANGLES,3);//begin
	triangleBatch.CopyVertexData3f(vVer);//Vertex's data of triangle
	triangleBatch.End();//end
}

//draw scene
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //clear the window with curent clearing color

	GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};  //设置三角形的填充颜色
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);   //use shader manager
	triangleBatch.Draw();  //draw triangle

	glutSwapBuffers();  //设置双缓冲区渲染环境
}

//main
int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);//设置当前工作目录
	glutInit(&argc,argv);   //传输命令行参数并初始化程序
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH  | GLUT_STENCIL);   //选择窗口的显示模式
	glutInitWindowSize(800,600);    //initialize window size
	glutCreateWindow("Triangle");   //create window
	glutReshapeFunc(ChangeSize);   //when size of window be changed, will be called 
	glutDisplayFunc(RenderScene);

	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr, "GLEW Error : %s\n", glewGetErrorString(err) );
		return 1;
	}

	SetupRC();  //预加载纹理、建立几何图形、渲染器等操作

	glutMainLoop();

	return 0;
}