// HistogramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageToolBox.h"
#include "HistogramDlg.h"
#include "afxdialogex.h"

#include "Dib.h"
#include "DibEnhancement.h"

// CHistogramDlg dialog

IMPLEMENT_DYNAMIC(CHistogramDlg, CDialogEx)

CHistogramDlg::CHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHistogramDlg::IDD, pParent)
{

}

CHistogramDlg::~CHistogramDlg()
{
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHistogramDlg message handlers

void CHistogramDlg::SetImage(CDib& dib)
{
	float histo[256] = { 0.f, };
	DibHistogram(dib, histo);

	register int i;
	float max_value = histo[0];
	for (i = 1; i < 256; i++)
	{
		if (histo[i] > max_value) max_value = histo[i];
	}

	for (i = 0; i < 256; i++)
	{
		m_Histogram[i] = (int)(histo[i] * 100 / max_value);
	}

}

void CHistogramDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

	register int i;

	dc.MoveTo(20, 30);
	dc.LineTo(20, 130);
	dc.LineTo(275, 130);
	dc.LineTo(275, 30);

	for (i = 0; i < 256; i++)
	{
		dc.MoveTo(20 + i, 130);
		dc.LineTo(20 + i, 130 - m_Histogram[i]);
	}

	for (i = 0; i < 256; i++)
	{
		dc.SelectStockObject(DC_PEN);
		dc.SetDCPenColor(RGB(i, i, i));

		dc.MoveTo(20 + i, 140);
		dc.LineTo(20 + i, 155);
	}

	dc.SelectStockObject(DC_PEN);
	dc.SetDCPenColor(RGB(128, 128, 128));

	int sum[256] = { 0, };
	sum[0] = m_Histogram[0];
	for (i = 1; i < 256; i++)
		sum[i] = sum[i - 1] + m_Histogram[i];

	dc.MoveTo(20, 130);
	for (i = 0; i < 256; i++)
	{
		dc.LineTo(20 + i, 130 - sum[i] * 100 / sum[255]);
	}
}
