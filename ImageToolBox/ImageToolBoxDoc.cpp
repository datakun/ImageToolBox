
// ImageToolBoxDoc.cpp : implementation of the CImageToolBoxDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageToolBox.h"
#endif

#include "ImageToolBoxDoc.h"

#include "Dib.h"
#include "DibEnhancement.h"

#include "FileNewDlg.h"
#include "BrightnessDlg.h"
#include "ContrastDlg.h"
#include "GammaCorrectionDlg.h"
#include "HistogramDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageToolBoxDoc

IMPLEMENT_DYNCREATE(CImageToolBoxDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageToolBoxDoc, CDocument)
	ON_COMMAND(ID_EDIT_COPY, &CImageToolBoxDoc::OnEditCopy)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CImageToolBoxDoc::OnGammaCorrection)
	ON_COMMAND(ID_HISTO_EQUALIZE, &CImageToolBoxDoc::OnHistoEqualize)
	ON_COMMAND(ID_IMAGE_BRIGHTNESS, &CImageToolBoxDoc::OnImageBrightness)
	ON_COMMAND(ID_IMAGE_CONTRAST, &CImageToolBoxDoc::OnImageContrast)
	ON_COMMAND(ID_IMAGE_INVERSE, &CImageToolBoxDoc::OnImageInverse)
	ON_COMMAND(ID_VIEW_HISTOGRAM, &CImageToolBoxDoc::OnViewHistogram)
END_MESSAGE_MAP()


// CImageToolBoxDoc construction/destruction

CImageToolBoxDoc::CImageToolBoxDoc()
{
	// TODO: add one-time construction code here

}

CImageToolBoxDoc::~CImageToolBoxDoc()
{
}

BOOL CImageToolBoxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	BOOL bSuccess = TRUE;

	if (theApp.m_pNewDib != NULL)
	{
		m_Dib.Copy(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}
	else
	{
		CFileNewDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			if (dlg.m_nType == 0) 
				bSuccess = m_Dib.CreateGrayImage(dlg.m_nWidth, dlg.m_nHeight);
			else 
				bSuccess = m_Dib.CreateRGBImage(dlg.m_nWidth, dlg.m_nHeight);
		}
		else
		{
			bSuccess = FALSE;
		}
	}

	return bSuccess;

}




// CImageToolBoxDoc serialization

void CImageToolBoxDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CImageToolBoxDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CImageToolBoxDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageToolBoxDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageToolBoxDoc diagnostics

#ifdef _DEBUG
void CImageToolBoxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageToolBoxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageToolBoxDoc commands


BOOL CImageToolBoxDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	return  m_Dib.Load(lpszPathName);
}


BOOL CImageToolBoxDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return  m_Dib.Save(lpszPathName);
}

void CImageToolBoxDoc::OnWindowDuplicate()
{
	AfxNewImage(m_Dib);
}

void CImageToolBoxDoc::OnEditCopy()
{
	// TODO: Add your command handler code here
	if (m_Dib.IsValid())
		m_Dib.CopyToClipboard();
}


void CImageToolBoxDoc::OnGammaCorrection()
{
	// TODO: Add your command handler code here
	CGammaCorrectionDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibGammaCorrection(dib, dlg.m_fGamma);
		AfxNewImage(dib);
	}
}


void CImageToolBoxDoc::OnHistoEqualize()
{
	// TODO: Add your command handler code here
	CDib dib = m_Dib;
	DibHistEqual(dib);
	AfxNewImage(dib);
}


void CImageToolBoxDoc::OnImageBrightness()
{
	// TODO: Add your command handler code here
	CBrightnessDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibBrightness(dib, dlg.m_nBrightness);
		AfxNewImage(dib);
	}
}


void CImageToolBoxDoc::OnImageContrast()
{
	// TODO: Add your command handler code here
	CContrastDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibContrast(dib, dlg.m_nContrast);
		AfxNewImage(dib);
	}
}


void CImageToolBoxDoc::OnImageInverse()
{
	// TODO: Add your command handler code here
	CDib dib = m_Dib;
	DibInverse(dib);
	AfxNewImage(dib);
}


void CImageToolBoxDoc::OnViewHistogram()
{
	// TODO: Add your command handler code here
	CHistogramDlg dlg;
	dlg.SetImage(m_Dib);
	dlg.DoModal();
}
