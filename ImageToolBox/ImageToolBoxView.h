
// ImageToolBoxView.h : interface of the CImageToolBoxView class
//

#pragma once


class CImageToolBoxView : public CScrollView
{
protected: // create from serialization only
	CImageToolBoxView();
	DECLARE_DYNCREATE(CImageToolBoxView)

// Attributes
public:
	CImageToolBoxDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CImageToolBoxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

protected:
	void SetScrollSizeToFit(void);
	void ShowImageInfo(CPoint point);

public:
	int m_nZoom;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnViewZoom1();
	afx_msg void OnViewZoom2();
	afx_msg void OnViewZoom3();
	afx_msg void OnViewZoom4();
	afx_msg void OnUpdateViewZoom1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewZoom2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewZoom3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewZoom4(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in ImageToolBoxView.cpp
inline CImageToolBoxDoc* CImageToolBoxView::GetDocument() const
   { return reinterpret_cast<CImageToolBoxDoc*>(m_pDocument); }
#endif

