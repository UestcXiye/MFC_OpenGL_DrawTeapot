
// OpenGLDrawingView.h : COpenGLDrawingView ��Ľӿ�
//

#pragma once
#include "Gl/gl.h"
#include "GL/glu.h"
#include "gl/glut.h"


class COpenGLDrawingView : public CView
{
protected: // �������л�����
	COpenGLDrawingView();
	DECLARE_DYNCREATE(COpenGLDrawingView)

// ����
public:
	COpenGLDrawingDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~COpenGLDrawingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // OpenGLDrawingView.cpp �еĵ��԰汾
inline COpenGLDrawingDoc* COpenGLDrawingView::GetDocument() const
   { return reinterpret_cast<COpenGLDrawingDoc*>(m_pDocument); }
#endif

