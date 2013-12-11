#pragma once


// CContrastDlg dialog

class CContrastDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CContrastDlg)

public:
	CContrastDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CContrastDlg();

// Dialog Data
	enum { IDD = IDD_CONTRAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CSliderCtrl m_sliderContrast;
	int m_nContrast;

public:
	afx_msg void OnEnChangeContrastEdit();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
};
