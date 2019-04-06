#include<Windows.h>
#include<gl/glut.h>
#include<gl/GL.h>
#include<cstdio>
#include "point.h"
#include "print.h"
//#include <opencv2/opencv.hpp>  
#include<iostream>


//using namespace cv;
using namespace std;

point p, p1;
int score = 2;
bool iflianshang = false;
bool start = 0;

double times = 60;

int* ImgBuffer;

/*void CVLoadTexture()
{
	IplImage * src = cvLoadImage("img.bmp", 1);
	Mat img(src);
	int imageWidth = src->width;
	int imageHeight = src->height;
	int imageSize = src->imageSize;


//******************************************************
	namedWindow("true", CV_WINDOW_AUTOSIZE);
	imshow("true", (Mat)src);
	//******************************************************




	
//	ImgBuffer = (int *)malloc(100);
	//int j = sizeof(ImgBuffer) / sizeof(int);;
	//int k;
	//int l;
	//j ++;
	//CvScalar ss;
	/*for (int i = 0; i < 10; i++)
	{
		j = i / 3 / imageWidth;
		k = (i - j * 3 * imageWidth) / 3;
		l = i % 3;
		ss = cvGet2D(src, j, k);
		//ImgBuffer[i] = img.at<Vec3b>(j , k)[2 - l];
		ImgBuffer[i] = (int)ss.val[2 - l];
		ImgBuffer[i];
	}
	//static int t = sizeof(ImgBuffer) / sizeof(int);
	memcpy(ImgBuffer, src->imageData, sizeof(unsigned char) * 100);
	int j = sizeof(ImgBuffer) / sizeof(int);
	j++;
	/*GLuint texName;
	glGenTextures(1, &texName);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, (GLubyte *)ImgBuffer);

	//******************************************************
	

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2i(0, 0);
	glTexCoord2d(0, 1);
	glVertex2i(0, 500);
	glTexCoord2d(1, 1);
	glVertex2i(400, 500);
	glTexCoord2d(1, 0);
	glVertex2i(400, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//******************************************************



	//cvReleaseImage(&src);
	//free(&ImgBuffer);
}*/

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);	//背景颜色
	glMatrixMode(GL_PROJECTION);	//
	gluOrtho2D(-50.0, 450.0, 0.0, 600.0);
	//glShadeModel(GL_SMOOTH);
}

void rezhe()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	char str[100];
	
	if (start)
	{
		
		
		p.pwx();
		p1.pwx();
		glColor3f(0.0, 0.0, 0.0);
		selectFont(30, ANSI_CHARSET, "楷体");
		sprintf(str, "score:%d", score);
		glWindowPos2i(0, 700);
		drawCNString(str);
		if (times <= 10)
			glColor3f(1, 0, 0);
		sprintf(str, "time:%d", (int)times);
		glWindowPos2i(600, 700);
		drawCNString(str);

		/*if (iflianshang)
		{
			strcpy(str, "已检测到人体");
		}
		else
		{
			strcpy(str, "未检测到人体");
		}
		glWindowPos2i(250, 730);
		drawCNString(str);*/
	}
	else
	{
		
		if (times <= 0)
		{
			glColor3f(0.0, 0.0, 0.0);
			sprintf(str, "score:%d", score);
			glWindowPos2i(600, 500);
			drawCNString(str);
		}
		selectFont(30, ANSI_CHARSET, "黑体");
		strcpy(str, "开始游戏");
		glWindowPos2i(350, 300);
		drawCNString(str);

		strcpy(str, "结束游戏");
		glWindowPos2i(900, 300);
		drawCNString(str);
		glBegin(GL_LINE_LOOP);
		glVertex2i(50, 300);
		glVertex2i(150, 300);
		glVertex2i(150, 200);
		glVertex2i(50, 200);		
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex2i(250, 300);
		glVertex2i(350, 300);
		glVertex2i(350, 200);
		glVertex2i(250, 200);
		glEnd();
	}
	
	glutSwapBuffers();
	glFlush();
	
}

void myIdle()
{
	if (start)
	{
		p.pwxyd(score);
		p1.pwxyd(score);
		times -= 0.1;
	}
	if (times <= 0)
	{
		start = 0;
	}
	rezhe();
}
int qx = 0;
int qy = 0;

void mousemove(int x, int y)
{
	int a = 500 * x / GetSystemMetrics(SM_CXSCREEN) - 50;
	int b = 600 - 600 * y / GetSystemMetrics(SM_CYSCREEN);
	if (qx == 0 && qy == 0)
	{
		qx = a;
		qy = b;
	}
	if ((p.ifpengdao(a, b) || p1.ifpengdao(a, b) ) && start)
	{
		score += 3 ;
		srand(time(NULL));
		int k = rand() % 3;
		switch (k)
		{
		case 1 :
			PlaySound(_T("切西瓜的声音(经典模式).wav"), NULL, SND_ASYNC);
			break;
		case 2:
			PlaySound(_T("切香蕉的声音(香蕉街机模式).wav"), NULL, SND_ASYNC);
			break;
		default:
			PlaySound(_T("切水果的声音：一切.wav"), NULL, SND_ASYNC);
			break;
		}
	}
		
	if (start == false)
	{
		if (a <= 150 && a >= 50 && b <= 300 && b >= 200)
		{
			
			PlaySound(_T("退出、返回的声音.wav"), NULL, SND_ASYNC);
			start = 1;
			times = 60;
			score = 2;
			glColor3f(0, 1, 0);
			glBegin(GL_QUADS);
			glVertex2i(50, 300);
			glVertex2i(150, 300);
			glVertex2i(150, 200);
			glVertex2i(50, 200);
			glEnd();
			glutSwapBuffers();
			glFlush();
			Sleep(1000);
		}
		if (a <= 350 && a >= 250 && b <= 300 && b >= 200)
		{
			//glutDestroyWindow(0);
			glColor3f(1, 0, 0);
			glBegin(GL_QUADS);
			glVertex2i(250, 300);
			glVertex2i(350, 300);
			glVertex2i(350, 200);
			glVertex2i(250, 200);
			glEnd();
			PlaySound(_T("退出、返回的声音.wav"), NULL, SND_ASYNC);
			glutSwapBuffers();
			glFlush();
			Sleep(1000);
			exit(0);
		}
		
	}
	glColor3f(0, 0, 0);
	if (a != qx)
	{
		glBegin(GL_LINES);
		{
			glVertex2i(qx, qy);
			glVertex2i(a, b);

			glVertex2i(qx, qy);
			glVertex2i(a, b + 1);

			glVertex2i(qx, qy);
			glVertex2i(a, b + 2);

			glVertex2i(qx, qy);
			glVertex2i(a, b + 3);

			glVertex2i(qx, qy);
			glVertex2i(a, b - 1);

			glVertex2i(qx, qy);
			glVertex2i(a, b - 2);

			glVertex2i(qx, qy);
			glVertex2i(a, b - 3);
		}
		glEnd();
	}
	else
	{
		glBegin(GL_LINES);
		{
			glVertex2i(qx, qy);
			glVertex2i(a, b);

			glVertex2i(qx, qy);
			glVertex2i(a + 1, b);

			glVertex2i(qx, qy);
			glVertex2i(a + 2, b);

			glVertex2i(qx, qy);
			glVertex2i(a + 3, b );

			glVertex2i(qx, qy);
			glVertex2i(a - 1, b);

			glVertex2i(qx, qy);
			glVertex2i(a - 2, b);

			glVertex2i(qx, qy);
			glVertex2i(a - 3, b);
		}
		glEnd();
	}

	glutSwapBuffers();
	//glutPostRedisplay();
	glFlush();
	qx = a;
	qy = b;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	glutCreateWindow("lzh");
	init();
	///DWORD t = (DWORD)GetActiveWindow();
	


	//ImgBuffer = new int[100];
	//CVLoadTexture();

	//initgraph(640, 480);
	//IMAGE *img = new IMAGE; // 定义 IMAGE 对象
	//loadimage(img, _T("img.jpg")); // 读取图片到 img 对象中
	//putimage(0, 0, img); // 在坐标 (0, 0) 位置显示 IMAGE 对象 
	//closegraph();


	




	glutDisplayFunc(rezhe);
	glutIdleFunc(&myIdle);
	glutPassiveMotionFunc(mousemove);
	glutMainLoop();
	
	return 0;
}
