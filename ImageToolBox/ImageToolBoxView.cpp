
// ImageToolBoxView.cpp : implementation of the CImageToolBoxView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageToolBox.h"
#endif

#include "ImageToolBoxDoc.h"
#include "ImageToolBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageToolBoxView

IMPLEMENT_DYNCREATE(CImageToolBoxView, CScrollView)

BEGIN_MESSAGE_MAP(CImageToolBoxView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CImageToolBoxView construction/destruction

CImageToolBoxView::CImageToolBoxView()
{
	// TODO: add construction code here

}

CImageToolBoxView::~CImageToolBoxView()
{
}

BOOL CImageToolBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CImageToolBoxView drawing

void CImageToolBoxView::OnDraw(CDC* pDC)
{
	CImageToolBoxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	if (pDoc->m_Dib.IsValid())
		pDoc->m_Dib.Draw(pDC->m_hDC);

}

void CImageToolBoxView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	CImageToolBoxDoc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		sizeTotal.cx = pDoc->m_Dib.GetWidth();
		sizeTotal.cy = pDoc->m_Dib.GetHeight();
	}
	else
	{
		sizeTotal.cx = sizeTotal.cy = 100;
	}
	
	SetScrollSizes(MM_TEXT, sizeTotal);
	ResizeParentToFit(TRUE);
}


// CImageToolBoxView printing

BOOL CImageToolBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageToolBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageToolBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CImageToolBoxView diagnostics

#ifdef _DEBUG
void CImageToolBoxView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageToolBoxView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageToolBoxDoc* CImageToolBoxView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageToolBoxDoc)));
	return (CImageToolBoxDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageToolBoxView message handlers


BOOL CImageToolBoxView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	CBrush br;
	br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
	FillOutsideRect(pDC, &br);

	return TRUE;
}
