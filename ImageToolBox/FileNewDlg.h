#pragma once


// CFileNewDlg dialog

class CFileNewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileNewDlg)

public:
	CFileNewDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileNewDlg();

// Dialog Data
	enum { IDD = IDD_FILE_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:	
	int m_nWidth;
	int m_nHeight;
	int m_nType;
};
