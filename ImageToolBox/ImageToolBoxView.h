
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
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in ImageToolBoxView.cpp
inline CImageToolBoxDoc* CImageToolBoxView::GetDocument() const
   { return reinterpret_cast<CImageToolBoxDoc*>(m_pDocument); }
#endif

