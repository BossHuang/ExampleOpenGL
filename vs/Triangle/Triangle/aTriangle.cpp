
//������ļ�
#include <GLTools.h>
#include <GLShaderManager.h>
//�����Ӧƽ̨��ͷ�ļ�
#ifdef _APPLE_
#include <glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch triangleBatch;
GLShaderManager  shaderManager;

void ChangeSize(int w, int h)   //����ά�ȱ��޸�ʱ����
{
	glViewport(0,0,w,h);
}

void SetupRC()   //Ԥ����������������ͼ�Ρ���Ⱦ���Ȳ���
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);   //���ñ���ɫ

	//��ɫ����ʼ��
	shaderManager.InitializeStockShaders();

	//��������
	GLfloat vVer[]={-0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.0f,};
	//������Ⱦ������
	triangleBatch.Begin(GL_TRIANGLES,3);//��ʼ
	triangleBatch.CopyVertexData3f(vVer);//�����ζ�������
	triangleBatch.End();//����
}

//������
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //ÿ�������ػ�ǰ���������ɫ����ȡ�ͼ��

	GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};  //���������ε������ɫ
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);   //ʹ����ɫ��
	triangleBatch.Draw();  //��������

	glutSwapBuffers();  //����˫��������Ⱦ����
}

//������
int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);//���õ�ǰ����Ŀ¼
	glutInit(&argc,argv);   //���������в�������ʼ������
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH  | GLUT_STENCIL);   //ѡ�񴰿ڵ���ʾģʽ
	glutInitWindowSize(800,600);    //��ʼ�����ڴ�С
	glutCreateWindow("Triangle");   //��������
	glutReshapeFunc(ChangeSize);   //����ά�ȱ����ĵ�ʱ�򱻵���
	glutDisplayFunc(RenderScene);

	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr, "GLEW Error : %s\n", glewGetErrorString(err) );
		return 1;
	}

	SetupRC();  //Ԥ����������������ͼ�Ρ���Ⱦ���Ȳ���

	glutMainLoop();

	return 0;
}