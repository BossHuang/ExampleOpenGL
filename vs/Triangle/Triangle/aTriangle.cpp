
//导入库文件
#include <GLTools.h>
#include <GLShaderManager.h>
//导入对应平台的头文件
#ifdef _APPLE_
#include <glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch triangleBatch;
GLShaderManager  shaderManager;

void ChangeSize(int w, int h)   //窗口维度被修改时调用
{
	glViewport(0,0,w,h);
}

void SetupRC()   //预加载纹理、建立几何图形、渲染器等操作
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);   //设置背景色

	//着色器初始化
	shaderManager.InitializeStockShaders();

	//画三角形
	GLfloat vVer[]={-0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.0f,};
	//批量渲染三角形
	triangleBatch.Begin(GL_TRIANGLES,3);//开始
	triangleBatch.CopyVertexData3f(vVer);//三角形顶点数据
	triangleBatch.End();//结束
}

//画场景
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //每个场景重画前的情况，颜色、深度、图案

	GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};  //设置三角形的填充颜色
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);   //使用着色器
	triangleBatch.Draw();  //画三角形

	glutSwapBuffers();  //设置双缓冲区渲染环境
}

//主函数
int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);//设置当前工作目录
	glutInit(&argc,argv);   //传输命令行参数并初始化程序
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH  | GLUT_STENCIL);   //选择窗口的显示模式
	glutInitWindowSize(800,600);    //初始化窗口大小
	glutCreateWindow("Triangle");   //创建窗口
	glutReshapeFunc(ChangeSize);   //窗口维度被更改的时候被调用
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