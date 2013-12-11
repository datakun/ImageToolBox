// BrightnessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageToolBox.h"
#include "BrightnessDlg.h"
#include "afxdialogex.h"


// CBrightnessDlg dialog

IMPLEMENT_DYNAMIC(CBrightnessDlg, CDialogEx)

CBrightnessDlg::CBrightnessDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CBrightnessDlg::IDD, pParent), m_nBrightness(0)
{

}

CBrightnessDlg::~CBrightnessDlg()
{
}

void CBrightnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BRIGHTNESS_EDIT, m_nBrightness);
	DDV_MinMaxInt(pDX, m_nBrightness, -100, 100);
	DDX_Control(pDX, IDC_BRIGHTNESS_SLIDER, m_sliderBrightness);
}


BEGIN_MESSAGE_MAP(CBrightnessDlg, CDialogEx)
	ON_EN_CHANGE(IDC_BRIGHTNESS_EDIT, &CBrightnessDlg::OnEnChangeBrightnessEdit)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CBrightnessDlg message handlers


void CBrightnessDlg::OnEnChangeBrightnessEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	m_sliderBrightness.SetPos(m_nBrightness);
}


void CBrightnessDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (m_sliderBrightness.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_sliderBrightness.GetPos();
		m_nBrightness = nPos;
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CBrightnessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_sliderBrightness.SetRange(-100, 100);
	m_sliderBrightness.SetTicFreq(20);
	m_sliderBrightness.SetPageSize(20);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
