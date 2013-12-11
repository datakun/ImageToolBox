#pragma once


// CBrightnessDlg dialog

class CBrightnessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBrightnessDlg)

public:
	CBrightnessDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBrightnessDlg();

// Dialog Data
	enum { IDD = IDD_BRIGHTNESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CSliderCtrl m_sliderBrightness;
	int m_nBrightness;

public:
	afx_msg void OnEnChangeBrightnessEdit();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
};
