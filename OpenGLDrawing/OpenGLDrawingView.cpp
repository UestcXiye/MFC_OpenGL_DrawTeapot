
// OpenGLDrawingView.cpp : COpenGLDrawingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OpenGLDrawing.h"
#endif

#include "OpenGLDrawingDoc.h"
#include "OpenGLDrawingView.h"
#include "Gl/gl.h"
#include "GL/glu.h"
#include "gl/glut.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLDrawingView

IMPLEMENT_DYNCREATE(COpenGLDrawingView, CView)

BEGIN_MESSAGE_MAP(COpenGLDrawingView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// COpenGLDrawingView 构造/析构

COpenGLDrawingView::COpenGLDrawingView()
{
	// TODO:  在此处添加构造代码
	m_xPos = 0.0f;
	m_yPos = 0.0f;
	m_zPos = 0.0f;
	m_xAngle = 0.0f;
	m_yAngle = 0.0f;
	m_zAngle = 0.0f;
	m_Scale = 1.0f;

}

COpenGLDrawingView::~COpenGLDrawingView()
{
}

BOOL COpenGLDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW);
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_MAXIMIZE;
	return CView::PreCreateWindow(cs);
}

// COpenGLDrawingView 绘制

void COpenGLDrawingView::OnDraw(CDC* /*pDC*/)
{
	COpenGLDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	if (m_hglrc)
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc);
	else
		return;
	
	//glRotatef(m_zAngle, 0.0f, 0.0f, 1.0f);
	glScalef(m_Scale, m_Scale, m_Scale);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(m_xPos, m_yPos, m_zPos);
	glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
	glScalef(m_Scale, m_Scale, m_Scale);
	glColor3f(1.0,1.0,0.0);
	glutWireTeapot(2);
	::SwapBuffers(m_pDC->GetSafeHdc());
	
}


// COpenGLDrawingView 打印

BOOL COpenGLDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COpenGLDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void COpenGLDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// COpenGLDrawingView 诊断

#ifdef _DEBUG
void COpenGLDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLDrawingDoc* COpenGLDrawingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLDrawingDoc)));
	return (COpenGLDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLDrawingView 消息处理程序


void COpenGLDrawingView::OnDestroy()
{
	// TODO:  在此处添加消息处理程序代码
	
	//Delete the rendering context  
	::wglMakeCurrent(NULL, NULL);
	if (m_hglrc)
		::wglDeleteContext(m_hglrc);
	if (m_pDC)
		delete m_pDC;
	CView::OnDestroy();
}


int COpenGLDrawingView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	int n;
	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);
	static PIXELFORMATDESCRIPTOR pfd =

	{

		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd  
		1,                              // version number  

		PFD_DRAW_TO_WINDOW |            // support window  

		PFD_SUPPORT_OPENGL |            // support OpenGL  

		PFD_DOUBLEBUFFER,                // double buffered  

		PFD_TYPE_RGBA,                  // RGBA type  
		24,                             // 24-bit color depth  
		0, 0, 0, 0, 0, 0,               // color bits ignored  
		0,                              // no alpha buffer  
		0,                              // shift bit ignored  
		0,                              // no accumulation buffer  
		0, 0, 0, 0,                     // accum bits ignored  
		16,                             // 16-bit z-buffer  
		0,                              // no stencil buffer  
		0,                              // no auxiliary buffer  
		PFD_MAIN_PLANE,                 // main layer  
		0,                              // reserved  
		0, 0, 0                         // layer masks ignored  

	};
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (m_nPixelFormat == 0)

	{
		return FALSE;
	}

	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return FALSE;
	}
	

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(),n,sizeof(pfd),&pfd);
	

	//Create Rendering Context  
	m_hglrc = ::wglCreateContext(m_pDC->GetSafeHdc());
	//Failure to Create Rendering Context  
	if (m_hglrc == 0)
	{
		MessageBox("Error Creating RC");
		return FALSE;
	}
	//Make the RC Current  
	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc) == FALSE)
	{
		MessageBox("Error making RC Current");
		return FALSE;
	}
	//Specify Black as the clear color  
	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Specify the back of the buffer as clear depth  
	::glClearDepth(1.0f);
	//Enable Depth Testing  
	::glEnable(GL_DEPTH_TEST);
	return 0;

}


void COpenGLDrawingView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if (m_hglrc)
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc);
	else
		return;

	// TODO:  在此处添加消息处理程序代码

	if (0 >= cx || 0 >= cy)
	{
		return;
	}
	 //select the full client area  
	::glViewport(0, 0, cx, cy);
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	if (cx < cy)
		glOrtho(-10.0, 100.0, -10.0*(GLfloat)cy / (GLfloat)cx, 10.0*(GLfloat)cy / (GLfloat)cx, -100.0, 100.0);
	else
		glOrtho(-10.0*(GLfloat)cx / (GLfloat)cy, 10.0*(GLfloat)cx / (GLfloat)cy, -10.0, 10.0, -100.0, 100.0);
	// switch back to the modelview matrix and clear it  
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}


void COpenGLDrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	m_MouseDownPoint = point;
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}


void COpenGLDrawingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	m_MouseDownPoint = CPoint(0, 0);
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}


BOOL COpenGLDrawingView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_Scale >= 0)
	{
		m_Scale += 0.05 *zDelta / 120;
	}
	else
	{
		if (zDelta > 0)
		{
			m_Scale += 0.05 *zDelta / 120;
		}
	}
	InvalidateRect(NULL, FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
	
}


void COpenGLDrawingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	if (GetCapture() == this)
	{
		//Increment the object rotation angles  
		m_xAngle += (point.y - m_MouseDownPoint.y) / 3.6;
		m_yAngle += (point.x - m_MouseDownPoint.x) / 3.6;
		//Redraw the view  
		InvalidateRect(NULL, FALSE);
		//Set the mouse point  
		m_MouseDownPoint = point;
	};
	CView::OnMouseMove(nFlags, point);
}


void COpenGLDrawingView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	switch (nChar)
	{
	case VK_UP:        m_yPos = m_yPos + 1.0f;
		break;
	case VK_DOWN:    m_yPos = m_yPos - 1.0f;
		break;
	case VK_LEFT:    m_xPos = m_xPos - 1.0f;
		break;
	case VK_RIGHT:  m_xPos = m_xPos + 1.0f;
		break;
	default:        MessageBox("Press the arrow keys only");
		break;
	}

	InvalidateRect(NULL, FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
