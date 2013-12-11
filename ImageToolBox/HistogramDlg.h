#pragma once


// CHistogramDlg dialog

class CHistogramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogramDlg)

public:
	CHistogramDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHistogramDlg();

// Dialog Data
	enum { IDD = IDD_HISTOGRAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_Histogram[256];

	void SetImage(CDib& dib);


	afx_msg void OnPaint();
};
