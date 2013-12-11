#pragma once


// CGammaCorrectionDlg dialog

class CGammaCorrectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGammaCorrectionDlg)

public:
	CGammaCorrectionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGammaCorrectionDlg();

// Dialog Data
	enum { IDD = IDD_GAMMA_CORRECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CSliderCtrl m_sliderGamma;
	float m_fGamma;

public:
	afx_msg void OnEnChangeGammaEdit();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
};
