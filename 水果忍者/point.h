#include<time.h>
#include<stdlib.h>
#include <graphics.h>
#include "Mmsystem.h"//playsound头文件
#pragma comment(lib, "winmm.lib")

class point
{
	int x;
	int y;
	int dx;
	int dy;

	double xs[3];
	int bae[3];
	bool ifinit;

	bool ifbreak;
	int luoxia;
	int kx;
	int ky;


	int n;
	double k;
	int i;
	
	double r;
	double g;
	double b;
	void toFindPwx()
	{
		srand(time(NULL));
		for (int i = 0; i < 2; i++)
		{
			bae[i] = (rand() + rand()) % (rand() % 400 + 1) ;
		}
		//bae[1] = bae[0];
		//bae[0] = 210;
		//bae[1] = 200;
		if (abs(bae[1] - bae[0]) <= 20)
		{
			bae[1] = bae[0];
			xs[0] = 0;
			xs[1] = 0;
			xs[2] = 0;
			return;
		}
		bae[2] = (bae[1] + bae[0]) / 2;
		xs[0] = 500.00 / (double)(bae[2] - bae[1]) / (double)(bae[2] - bae[0]);
		xs[1] = -xs[0] * (bae[1] + bae[0]);
		xs[2] = xs[0] * bae[1] * bae[0];
	}
	void DrawQuad()
	{
		glBegin(GL_QUADS);
		glVertex2i(x - dx, y - dy);
		glVertex2i(x - dx, y);
		glVertex2i(x + dx, y);
		glVertex2i(x + dx, y - dy);
		glEnd();
	}
public:
	point()
	{
		ifinit = 1;
		ifbreak = 1;
		n = 0;
		k = 0;
		i = 0;
		dx = 20;
		dy = 40;
		r = 0;
		g = 0;
		b = 0;
		luoxia = 0;
		kx = 0;
		ky = 0;
	}
	void pwx()		//rezhe
	{
		glColor3f(r, g, b);
		if (ifinit)
		{
			ifinit = 0;
			toFindPwx();
			if (bae[0] != bae[1])
			{
				n = abs(bae[0] - bae[1]);
				k = (bae[1] - bae[0]) / n;
			}
			else
			{
				n = 100;
			}
		}

		if (bae[0] != bae[1] && ifbreak)
		{
			x = bae[0] + k * i;
			y = xs[0] * x * x + xs[1] * x + xs[2];
			DrawQuad();
		}
		else if (bae[0] == bae[1] && ifbreak)
		{
			x = bae[1];
			if (i <= 50)
			{
				y = 8 * i;
				DrawQuad();
			}
			else
			{
				y = 800 - 8 * i;
				DrawQuad();
			}
		}
		else
		{

		}
	}
	void pwxyd(int& score)		//myidle
	{
		if (n)
			Sleep(100 / n + 30);
		if (i < n)
		{
			i++;
		}
		else
		{
			srand(time(NULL));
			r = (double)(rand() % 255) / 255;
			g = (double)(rand() % 255) / 255;
			b = (double)(rand() % 255) / 255;
			//PlaySound(_T("扔水果上来的声音.wav"), NULL, SND_ASYNC);
			i = 0;
			ifinit = 1;
			score -= 1;
		}
	}
	bool ifpengdao(int xt, int yt)
	{
		//xt = x;
		//yt = y;
		glColor3f(r, g, b);
		if (xt <= x + dx && xt >= x - dx && yt <= y && yt >= y - dy)
		{
			i = n + 1;
			ifinit = 1;
			ifbreak = 1;
			//n += y / 5;
			luoxia = i;
			//kx = (bae[0] - x) / 
			return true;
		}
		return false;
	}
};
