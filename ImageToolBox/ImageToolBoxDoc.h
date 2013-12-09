
// ImageToolBoxDoc.h : interface of the CImageToolBoxDoc class
//


#pragma once
#include "D:\SigmaDream\Desktop\영상처리 스터디 자료\IT EXPERT - 영상 처리 프로그래밍 by Visual C++_소스\source\ch04\DibCreate\Dib.h"


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
	BOOL OnOpenDocument(LPCTSTR lpszPathName);
	BOOL OnSaveDocument(LPCTSTR lpszPathName);
	// Image Object
	CDib m_Dib;
};
