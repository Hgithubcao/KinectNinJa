#include<gl/glut.h>
#include<Windows.h>

void glWindowPos2i(GLint x, GLint y)
{
	typedef void(__stdcall * ARBFUNC)(GLint x, GLint y);
	ARBFUNC glptr = 0;
	glptr = (ARBFUNC)wglGetProcAddress("glWindowPos2iARB");

	if (glptr)
		glptr(x, y);
	else
	{
		//glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		glVertex3i(-100, -100, -100);
		glVertex3i(100, 100, 100);
		glEnd();
		GLint viewport[4];
		GLdouble modelview[16], projection[16];
		GLdouble x1, y1, z;

		//printf("不支持GL_ARB_window_pos\n");
		//printf("使用glRasterPos函数\n");

		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		gluUnProject(x, y, 0, modelview, projection, viewport,
			&x1, &y1, &z);
		glRasterPos3d(x1, y1, z);
	}
}

void drawCNString(const char* str) {
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);
	len = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// 逐个输出字符
	for (i = 0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// 回收所有临时资源
	free(wstring);
	glDeleteLists(list, 1);
	// 将混合字符转化为宽字符  
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';
	// 用完后记得释放内存  
	free(wstring);
}

void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}