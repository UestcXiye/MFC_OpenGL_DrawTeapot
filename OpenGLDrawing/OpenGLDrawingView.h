
// OpenGLDrawingView.h : COpenGLDrawingView 类的接口
//

#pragma once
#include "Gl/gl.h"
#include "GL/glu.h"
#include "gl/glut.h"


class COpenGLDrawingView : public CView
{
protected: // 仅从序列化创建
	COpenGLDrawingView();
	DECLARE_DYNCREATE(COpenGLDrawingView)

// 特性
public:
	COpenGLDrawingDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~COpenGLDrawingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	CClientDC *m_pDC;
	HGLRC m_hglrc;
	GLfloat m_yAngle;
	GLfloat m_xAngle;
	GLfloat m_zAngle;
	GLfloat m_xPos;
	GLfloat m_yPos;
	GLfloat m_zPos;
	CPoint m_MouseDownPoint;
	float m_Scale;
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // OpenGLDrawingView.cpp 中的调试版本
inline COpenGLDrawingDoc* COpenGLDrawingView::GetDocument() const
   { return reinterpret_cast<COpenGLDrawingDoc*>(m_pDocument); }
#endif

