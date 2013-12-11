// ContrastDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageToolBox.h"
#include "ContrastDlg.h"
#include "afxdialogex.h"


// CContrastDlg dialog

IMPLEMENT_DYNAMIC(CContrastDlg, CDialogEx)

CContrastDlg::CContrastDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CContrastDlg::IDD, pParent), m_nContrast(0)

{

}

CContrastDlg::~CContrastDlg()
{
}

void CContrastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CONTRAST_EDIT, m_nContrast);
	DDV_MinMaxInt(pDX, m_nContrast, -100, 100);
	DDX_Control(pDX, IDC_CONTRAST_SLIDER, m_sliderContrast);
}


BEGIN_MESSAGE_MAP(CContrastDlg, CDialogEx)
	ON_EN_CHANGE(IDC_CONTRAST_EDIT, &CContrastDlg::OnEnChangeContrastEdit)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CContrastDlg message handlers


void CContrastDlg::OnEnChangeContrastEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	m_sliderContrast.SetPos(m_nContrast);
}


void CContrastDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (m_sliderContrast.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_sliderContrast.GetPos();
		m_nContrast = nPos;
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CContrastDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_sliderContrast.SetRange(-100, 100);
	m_sliderContrast.SetTicFreq(20);
	m_sliderContrast.SetPageSize(20);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
