
// OpenGLDrawing.h : OpenGLDrawing Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// COpenGLDrawingApp:
// �йش����ʵ�֣������ OpenGLDrawing.cpp
//

class COpenGLDrawingApp : public CWinApp
{
public:
	COpenGLDrawingApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLDrawingApp theApp;
