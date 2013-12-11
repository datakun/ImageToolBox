
// ImageToolBoxDoc.h : interface of the CImageToolBoxDoc class
//


#pragma once
#include "Dib.h"


class CImageToolBoxDoc : public CDocument
{
protected: // create from serialization only
	CImageToolBoxDoc();
	DECLARE_DYNCREATE(CImageToolBoxDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CImageToolBoxDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	// Image Object
	CDib m_Dib;
	afx_msg void OnWindowDuplicate();
	afx_msg void OnEditCopy();
	afx_msg void OnGammaCorrection();
	afx_msg void OnHistoEqualize();
	afx_msg void OnImageBrightness();
	afx_msg void OnImageContrast();
	afx_msg void OnImageInverse();
	afx_msg void OnViewHistogram();
};
