//////////////////////////////////////////////////////////////////////
//                                                                  //
// Dib.cpp: implementation of the CDib class.                       //
//                                                                  //
// Copyright (c) 2003~<current> Sun-Kyoo Hwang                      //
//                              sunkyoo.ippbook@gmail.com           //
//                                                                  //
// ����ó�� ���α׷��� By Visual C++                                //
//                                                                  //
// Last modified: 10/04/2007                                        //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Dib.h"
#include "RGBBYTE.h"

/*************************************************************************
* 
* �̸� : CDib()
* ���� : ����.
* ��ȯ : ����.
* ���� : �⺻ ������. ��� ���� �ʱ�ȭ.
* 
*************************************************************************/

CDib::CDib()
{
	// ��� ���� �ʱ�ȭ
	m_nWidth     = 0;
	m_nHeight    = 0;
	m_nBitCount  = 0;
	m_nDibSize   = 0;

	m_pDib       = NULL;

	m_pPtr       = NULL;
	m_pRgbPtr    = NULL;
}

/*************************************************************************
* 
* �̸� : CDib(const CDib& dib)
* ���� : dib - ������ CDib ��ü.
* ��ȯ : ����.
* ���� : ���� ������. ���ڷ� �Ѿ�� dib ��ü�� �����Ѵ�.
* 
*************************************************************************/

CDib::CDib(const CDib& dib)
{
	// ��� ���� �ʱ�ȭ
	m_nWidth     = 0;
	m_nHeight    = 0;
	m_nBitCount  = 0;

	m_nDibSize   = 0;

	m_pDib       = NULL;

	m_pPtr       = NULL;
	m_pRgbPtr    = NULL;

	if( dib.m_pDib != NULL )
	{
		// ���ڷκ��� DIB ������ �����Ѵ�.
		m_pDib = new BYTE[dib.m_nDibSize];
		memcpy(m_pDib, dib.m_pDib, dib.m_nDibSize);

		// ��� ���� �� ����
		InitDib();
	}
}

/*************************************************************************
* 
* �̸� : ~CDib()
* ���� : ����.
* ��ȯ : ����.
* ���� : �Ҹ���. DIB ��ü�� �����Ѵ�.
* 
*************************************************************************/

CDib::~CDib()
{
	Destroy();
}

/*************************************************************************
* 
* �̸� : CreateGrayImage(int nWidth, int nHeight, BYTE value)
* ���� : nWidth  - ������ DIB�� ���� ũ��(�ȼ� ����)
*        nHeight - ������ DIB�� ���� ũ��(�ȼ� ����)
*        value   - �ȼ� �ʱⰪ, ����Ʈ ���� 255.
* ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
* ���� : ������ ũ���� �׷��̽����� ������ �����Ѵ�.
*        ����, ���� DIB ��ü�� ������ �ִٸ� ���� �� �����Ѵ�.
* 
*************************************************************************/

BOOL CDib::CreateGrayImage(int nWidth, int nHeight, BYTE value)
{
	// ���� ������ CDib ��ü�� �ִٸ� �����Ѵ�.
	if( m_pDib ) Destroy();

	int nBitCount = 8;       // �׷��̽����� �̹����� ��Ʈ �� �ȼ� ��

	// ���� ���� �������� ũ��(����Ʈ ����)
	DWORD dwSizeImage = nHeight * (DWORD)((nWidth*nBitCount/8+3)&~3);

	// (BITMAPINFOHEADER + ���� ���̺� + �ȼ� ������)�� ���� �޸� ���� �Ҵ�
	m_pDib = new BYTE[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*(1<<nBitCount) + dwSizeImage];
	if( m_pDib == NULL ) return FALSE;

	// BITMAPINFOHEADER ����ü �ʵ� ���� �����Ѵ�.
	LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;

	lpbmi->biSize           = sizeof(BITMAPINFOHEADER);
	lpbmi->biWidth          = nWidth;
	lpbmi->biHeight         = nHeight;
	lpbmi->biPlanes         = 1;
	lpbmi->biBitCount       = nBitCount;
	lpbmi->biCompression    = BI_RGB;
	lpbmi->biSizeImage      = dwSizeImage;
	lpbmi->biXPelsPerMeter  = 0;
	lpbmi->biYPelsPerMeter  = 0;
	lpbmi->biClrUsed        = 0;
	lpbmi->biClrImportant   = 0;

	// ���� ���̺� ���� �׷��̽����� ���·� �����Ѵ�.
	RGBQUAD* pPal = (RGBQUAD*)((BYTE*)m_pDib + sizeof(BITMAPINFOHEADER));
	for( int i = 0 ; i < 256 ; i++ )
	{
		pPal->rgbBlue  = (BYTE)i;
		pPal->rgbGreen = (BYTE)i;
		pPal->rgbRed   = (BYTE)i;
		pPal->rgbReserved = 0;
		pPal++;
	}

	// ��� ���� �� ����
	InitDib();

	// �ȼ� ������ �� �ʱ�ȭ
	BYTE* pData = (BYTE*)GetDibBitsAddr();
	memset(pData, value, dwSizeImage);

	return TRUE;
}

/*************************************************************************
* 
* �̸� : CreateRGBImage(int nWidth, int nHeight, COLORREF value)
* ���� : nWidth  - ������ DIB�� ���� ũ��(�ȼ� ����)
*        nHeight - ������ DIB�� ���� ũ��(�ȼ� ����)
*        value   - �ȼ� �ʱⰪ, ����Ʈ ���� RGB(255, 255, 255).
* ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
* ���� : ������ ũ���� Ʈ��Į�� ������ �����Ѵ�.
*        ����, ���� DIB ��ü�� ������ �ִٸ� ���� �� �����Ѵ�.
* 
*************************************************************************/

BOOL CDib::CreateRGBImage(int nWidth, int nHeight, COLORREF value)
{
	// ���� ������ CDib ��ü�� �ִٸ� �����Ѵ�.
	if( m_pDib ) Destroy();

	int nBitCount = 24;       // Ʈ��Į�� �̹���

	// ���� ���� �������� ũ��(����Ʈ ����)
	DWORD dwSizeImage = nHeight * (DWORD)((nWidth*nBitCount/8+3)&~3);

	// (BITMAPINFOHEADER + �ȼ� ������)�� ���� �޸� ���� �Ҵ�
	m_pDib = new BYTE[sizeof(BITMAPINFOHEADER) + dwSizeImage];
	if( m_pDib == NULL ) return FALSE;

	// BITMAPINFOHEADER ����ü �ʵ� ���� �����Ѵ�.
	LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;

	lpbmi->biSize           = sizeof(BITMAPINFOHEADER);
	lpbmi->biWidth          = nWidth;
	lpbmi->biHeight         = nHeight;
	lpbmi->biPlanes         = 1;
	lpbmi->biBitCount       = nBitCount;
	lpbmi->biCompression    = BI_RGB;
	lpbmi->biSizeImage      = dwSizeImage;
	lpbmi->biXPelsPerMeter  = 0;
	lpbmi->biYPelsPerMeter  = 0;
	lpbmi->biClrUsed        = 0;
	lpbmi->biClrImportant   = 0;

	// ��� ���� �� ����
	InitDib();

	// �ȼ� �� �ʱ�ȭ
	register int i, j;
	for( j = 0 ; j < m_nHeight ; j++ )
	for( i = 0 ; i < m_nWidth  ; i++ )
	{
		// RGBBYTE Ŭ�������� = �� operator overloading �Ǿ��ִ�.
		m_pRgbPtr[j][i] = value;	
	}

	return TRUE;
}

/*************************************************************************
* 
* �̸� : InitDib()
* ���� : ����.
* ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
* ���� : m_nWidth, m_nHeight, m_nBitCount���� ��� ������ ���� �����Ѵ�.
*        m_pDib�� BITMAPINFOHEADER�� ���۹����� ����Ű�� �ִ� ��Ȳ����
*        ȣ��Ǿ�� �Ѵ�. m_pPtr, m_pRgbPtr �������̽� ���� �����Ѵ�.
* 
*************************************************************************/

BOOL CDib::InitDib()
{
	LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;

	// �̹����� ���� ũ��, ���� ũ��, �ȼ��� ��Ʈ��, DIB ũ�⿡ ����
	// ��� ������ �����Ѵ�.
	m_nWidth    = lpbmi->biWidth;
	m_nHeight   = lpbmi->biHeight;
	m_nBitCount = lpbmi->biBitCount;

	DWORD dwSizeImage = m_nHeight * (DWORD)((m_nWidth*m_nBitCount/8+3)&~3);

	m_nDibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*GetPaletteNums() 
		+ dwSizeImage;

	// m_pPtr �Ǵ� m_pRgbPtr ��� ������ �����Ѵ�.
	if( !AllocPtr() )
		return FALSE;

	return TRUE;
}

/*************************************************************************
* 
* �̸� : Destroy()
* ���� : ����.
* ��ȯ : ����.
* ���� : �������� �Ҵ�� ��� �����͸� �����ϰ�, NULL�� �����Ѵ�.
*        ��Ÿ ��� ������ �ʱ�ȭ�Ѵ�.
* 
*************************************************************************/

void CDib::Destroy()
{
	if( m_pDib )	
	{
		delete [] m_pDib;
		m_pDib = NULL;
	}

	FreePtr();  // m_pPtr �� m_pRgbPtr ��� ������ �Ҹ��Ų��.

	// ��Ÿ ��� ���� �ʱ�ȭ
	m_nWidth    = 0;
	m_nHeight   = 0;
	m_nBitCount = 0;
	m_nDibSize  = 0;
}

/*************************************************************************
* 
* �̸� : operator=(const CDib& dib)
* ���� : pDib - ������ CDib ��ü.
* ��ȯ : CDib ��ü�� ������.
* ���� : ���ڷ� �Ѿ�� dib�� ������ CDib ��ü�� �����Ѵ�.
* 
*************************************************************************/

CDib& CDib::operator=(const CDib& dib)
{
	// ��� �˻�
	if( this == &dib )
		return *this;

	// dib�� ����ִ� CDib ��ü��� �ڽŵ� ����.
	if( dib.m_pDib == NULL )
	{
		Destroy();
		return *this;
	}

	// ���� ������ CDib ��ü�� �ִٸ� �����Ѵ�.
	if( m_pDib ) Destroy();

	// (BITMAPINFOHEADER + �ȼ� ������)�� ���� �޸� ���� �Ҵ�
	m_pDib = new BYTE[dib.m_nDibSize];

	// DIB ���� ����
	memcpy(m_pDib, dib.m_pDib, dib.m_nDibSize);

	// ��� ���� �� ����
	InitDib();

	return *this;
}

/*************************************************************************
* 
* �̸� : Copy(CDib* pDib)
* ���� : pDib - ������ CDib ��ü�� ������.
* ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
* ���� : ���ڷ� �Ѿ�� pDib�� ����Ű�� CDib ��ü�� �����Ѵ�.
* 
*************************************************************************/

BOOL CDib::Copy(CDib* pDib)
{
	// pDib�� ����ִ� CDib ��ü�� ����Ű�� �ִٸ� �ڽŵ� ����.
	if( !pDib->IsValid() )
	{
		Destroy();
		return TRUE;
	}

	// ���� ������ CDib ��ü�� �ִٸ� �����Ѵ�.
	if( m_pDib ) Destroy();

	// DIB�� ���� �޸� ���� �Ҵ�
	DWORD dwDibSize = pDib->GetDibSize();
	m_pDib = new BYTE[dwDibSize];
	if( m_pDib == NULL )
		return FALSE;

	// DIB ���� ����
	BYTE* pbi = (BYTE*)pDib->GetBitmapInfoAddr();
	memcpy(m_pDib, pbi, dwDibSize);

	// ��� ���� �� ����
	InitDib();

	return TRUE;
}

/*************************************************************************
* 
* �̸� : Load(LPCTSTR lpszFileName)
* ���� : lpszFileName - �ҷ��� ������ ��ü ��� �̸�.
* ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
* ���� : BMP ������ CDib ��ü�� �ҷ��´�.
*        Ȯ���ڸ� �˻��Ͽ� BMP �����̸� LoadBMP �Լ��� �ٽ� ȣ���Ѵ�.
* 
*************************************************************************/

BOOL CDib::Load(LPCTSTR lpszFileName)
{
	CString filetype;
	filetype = lpszFileName;
	filetype.MakeUpper();

	if( filetype.Right(4) == ".BMP" ) 
		return LoadBMP(lpszFileName);
	else 
		return FALSE;
}

/*************************************************************************
* 
* �̸� : Save(LPCTSTR lpszFileName)
* ���� : lpszFileName - �ҷ��� ������ ��ü ��� �̸�.
* ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
* ���� : CDib ��ü�� BMP ���Ϸ� �����Ѵ�.
*        Ȯ���ڸ� �˻��Ͽ� BMP �����̸� SaveBMP �Լ��� �ٽ� ȣ���Ѵ�.
* 
*************************************************************************/

BOOL CDib::Save(LPCTSTR lpszFileName)
{
	CString filetype;
	filetype = lpszFileName;
	filetype.MakeUpper();

	if( filetype.Right(4) == ".BMP" ) 
		return SaveBMP(lpszFileName);
	else 
		return FALSE;
}

/*************************************************************************
* 
* �̸� : Draw(HDC hDC)
* ���� : hDC - ��� ��ġ�� DC �ڵ�.
* ��ȯ : ����.
* ���� : ��� ��ġ ��ǥ (0,0) ��ġ�� DIB�� ����Ѵ�.
* 
*************************************************************************/

void CDib::Draw(HDC hDC)
{
	Draw(hDC, 0, 0);
}

/*************************************************************************
* 
* �̸� : Draw(HDC hDC)
* ���� : hDC - ��� ��ġ�� DC �ڵ�.
*        dx  - ��� ��ġ ��ġ�� x ��ǥ.
*        dy  - ��� ��ġ ��ġ�� y ��ǥ.
* ��ȯ : ����.
* ���� : ��� ��ġ ��ǥ (dx,dy) ��ġ�� DIB�� ����Ѵ�.
* 
*************************************************************************/

void CDib::Draw(HDC hDC, int dx, int dy)
{
	if( m_pDib == NULL )
		return;

	LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
	void* lpBits = (void*)GetDibBitsAddr();

	::SetDIBitsToDevice(hDC,	// hDC
		dx,					// DestX
		dy,					// DestY
		m_nWidth,			// nSrcWidth
		m_nHeight,			// nSrcHeight
		0,					// SrcX
		0,					// SrcY
		0,					// nStartScan
		m_nHeight,			// nNumScans
		lpBits,				// lpBits
		lpbi,				// lpBitsInfo
		DIB_RGB_COLORS);	// wUsage
}

/*************************************************************************
* 
* �̸� : Draw(HDC hDC)
* ���� : hDC - ��� ��ġ�� DC �ڵ�.
*        dx  - ����� ��ġ�� x ��ǥ.
*        dy  - ����� ��ġ�� y ��ǥ.
*        dw  - ����� ������ ���� ũ��
*        dh  - ����� ������ ���� ũ��
*        dwRop - ������ ���۷��̼� ����.
* ��ȯ : ����.
* ���� : ��� ��ġ ��ǥ (dx,dy) ��ġ�� (dw, dh) ũ��� DIB�� ����Ѵ�.
* 
*************************************************************************/

void CDib::Draw(HDC hDC, int dx, int dy, int dw, int dh, DWORD dwRop)
{
	if( m_pDib == NULL )
		return;

	LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
	LPSTR lpDIBBits = (LPSTR)GetDibBitsAddr();

	::StretchDIBits(hDC,	// hDC
		dx,					// XDest
		dy,					// YDest
		dw,					// nDestWidth
		dh,					// nDestHeight
		0,					// XSrc
		0,					// YSrc
		m_nWidth,			// nSrcWidth
		m_nHeight,			// nSrcHeight
		lpDIBBits,			// lpBits
		lpbi,				// lpBitsInfo
		DIB_RGB_COLORS,		// wUsage
		SRCCOPY);			// dwROP
}

/*************************************************************************
* 
* �̸� : Draw(HDC hDC)
* ���� : hDC - ��� ��ġ�� DC �ڵ�.
*        dx  - ����� ��ġ�� x ��ǥ.
*        dy  - ����� ��ġ�� y ��ǥ.
*        dw  - ����� ������ ���� ũ��
*        dh  - ����� ������ ���� ũ��
*        sx  - ���� ������ �»�� x ��ǥ.
*        sy  - ���� ������ �»�� y ��ǥ.
*        sw  - ���� ���󿡼� ����� ������ ���� ũ��
*        sh  - ���� ���󿡼� ����� ������ ���� ũ��
*        dwRop - ������ ���۷��̼� ����.
* ��ȯ : ����.
* ���� : ��� ��ġ ��ǥ (dx,dy) ��ġ�� (dw, dh) ũ��� DIB�� ����Ѵ�.
* 
*************************************************************************/

void CDib::Draw(HDC hDC, int dx, int dy, int dw, int dh, 
				int sx, int sy, int sw, int sh, DWORD dwRop)
{
	if( m_pDib == NULL )
		return;

	LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
	LPSTR lpDIBBits = (LPSTR)GetDibBitsAddr();

	::StretchDIBits(hDC,	// hDC
		dx,					// XDest
		dy,					// YDest
		dw,					// nDestWidth
		dh,					// nDestHeight
		sx,					// XSrc
		sy,					// YSrc
		sw,					// nSrcWidth
		sh,					// nSrcHeight
		lpDIBBits,			// lpBits
		lpbi,				// lpBitsInfo
		DIB_RGB_COLORS,		// wUsage
		SRCCOPY);			// dwROP
}

/*************************************************************************
* 
* �̸� : GetDibBitsAddr()
* ���� : ����.
* ��ȯ : �ȼ� �������� ���� �ּҸ� ��ȯ.
* ���� : m_pDib�� �����Ͽ�, �ȼ� �������� ���� �ּҸ� ��ȯ�Ѵ�.
* 
*************************************************************************/

LPVOID CDib::GetDibBitsAddr()
{
	LPBITMAPINFOHEADER lpbmi;
	LPVOID lpDibBits;

	lpbmi = (LPBITMAPINFOHEADER)m_pDib;
	lpDibBits = (LPVOID)((BYTE*)m_pDib + lpbmi->biSize 
		+ sizeof(RGBQUAD)*GetPaletteNums());

	return lpDibBits;
}

/*************************************************************************
* 
* �̸� : GetPaletteNums()
* ���� : ����.
* ��ȯ : �ȷ�Ʈ���� RGBQUAD �迭�� ����.
* ���� : �ȷ�Ʈ���� �ʿ��� RGBQUAD ����ü �迭�� ������ ��ȯ�Ѵ�.
*        Ʈ��Į���̸� 0�� ��ȯ�Ѵ�.
* 
*************************************************************************/

int CDib::GetPaletteNums()
{
	switch( m_nBitCount )
	{
		case 1:     return 2;
		case 4:     return 16;
		case 8:     return 256;
		default:    return 0;
	}
}

/*************************************************************************
* 
* �̸� : AllocPtr()
* ���� : ����.
* ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
* ���� : m_pPtr, m_pRgbPtr �������̽��� �����Ѵ�.
*        �ȼ� �����Ͱ� bottom-up ���·� ����Ǿ��ִٰ� �����Ѵ�.
* 
*************************************************************************/

BOOL CDib::AllocPtr()
{
	if( m_nBitCount == 8 )        // �׷��̽����� �̹���
	{
		if( m_pPtr ) FreePtr();
		m_pPtr = new BYTE*[m_nHeight];
		if( !m_pPtr ) return FALSE;

		int nRWidth = ((m_nWidth*m_nBitCount/8+3)&~3);
		BYTE* pData = (BYTE*)GetDibBitsAddr();
		for( int i = 0 ; i < m_nHeight ; i++ )
			m_pPtr[i] = (BYTE*)(pData + (m_nHeight-i-1)*nRWidth);
	}
	else if( m_nBitCount == 24 )  // Ʈ��Į�� �̹���
	{
		if( m_pRgbPtr ) FreePtr();
		m_pRgbPtr = new RGBBYTE*[m_nHeight];
		if( !m_pRgbPtr ) return FALSE;

		int nRWidth = ((m_nWidth*m_nBitCount/8+3)&~3);
		BYTE* pData = (BYTE*)GetDibBitsAddr();
		for( int i = 0 ; i < m_nHeight ; i++ )
			m_pRgbPtr[i] = (RGBBYTE*)(pData + (m_nHeight-i-1)*nRWidth);
	}
	else
		return FALSE;

	return TRUE;
}

/*************************************************************************
* 
* �̸� : FreePtr()
* ���� : ����.
* ��ȯ : ����.
* ���� : m_pPtr, m_pRgbPtr �������̽��� �����Ѵ�.
* 
*************************************************************************/

void CDib::FreePtr()
{
	if( m_pPtr != NULL )
	{
		delete [] m_pPtr;
		m_pPtr = NULL;
	}

	if( m_pRgbPtr != NULL )
	{
		delete [] m_pRgbPtr;
		m_pRgbPtr = NULL;
	}
}

/*************************************************************************
* 
* �̸� : CopyToClipboard()
* ���� : ����.
* ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
* ���� : DIB ������ clipboard�� �����Ѵ�.
* 
*************************************************************************/

BOOL CDib::CopyToClipboard()
{
	int     dwSizeDib;
	HANDLE  hDib;

	if( !::OpenClipboard( NULL ) )	return FALSE;

	// DIB ��ü�� ���� �޸� ���� ����

	dwSizeDib = GetDibSize();
	hDib = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE, dwSizeDib);
	if( hDib == NULL )	
	{
		::CloseClipboard();
		return FALSE;
	}

	void* lpDib = ::GlobalLock((HGLOBAL)hDib);
	memcpy(lpDib, GetBitmapInfoAddr(), dwSizeDib);
	::GlobalUnlock(hDib);

	// Ŭ�����忡 ������ �Է�

	::EmptyClipboard();
	::SetClipboardData(CF_DIB, hDib);
	::CloseClipboard();

	return TRUE;
}

/*************************************************************************
* 
* �̸� : PasteFromClipboard()
* ���� : ����.
* ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
* ���� : Clipboard�κ��� DIB ������ �����´�.
* 
*************************************************************************/

BOOL CDib::PasteFromClipboard()
{
	HANDLE  hDib;
	DWORD   dwSize;
	void*   lpDib;

	// CF_DIB Ÿ���� �ƴϸ� �����Ѵ�.
	if( !::IsClipboardFormatAvailable(CF_DIB) ) return FALSE;

	// Ŭ�� ���带 ����.
	if( !::OpenClipboard(NULL) ) return FALSE;

	// Ŭ�� ���� ������ �޾ƿ´�.
	hDib = ::GetClipboardData(CF_DIB);
	if( hDib == NULL ) 
	{
		::CloseClipboard();
		return FALSE;
	}

	// �޸� ���� ũ��� DIB ��ü ũ��� ����
	dwSize = (DWORD)::GlobalSize((HGLOBAL)hDib);
	lpDib = ::GlobalLock((HGLOBAL)hDib);

	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)lpDib;
	LONG nWidth    = lpbi->biWidth;
	LONG nHeight   = lpbi->biHeight;
	WORD nBitCount = lpbi->biBitCount;
	DWORD dwSizeDib;

	DWORD dwSizeImage = nHeight * (DWORD)((nWidth*nBitCount/8+3)&~3);
	if( nBitCount == 8 )
		dwSizeDib = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*(1<<nBitCount) + dwSizeImage;
	else
		dwSizeDib = sizeof(BITMAPINFOHEADER) + dwSizeImage;

	// ���� ������ CDib ��ü�� �ִٸ� �����Ѵ�.
	if( m_pDib ) Destroy();

	m_pDib = new BYTE[dwSizeDib];
	memcpy(m_pDib, lpDib, dwSizeDib);

	::GlobalUnlock(hDib);

	::CloseClipboard();

	// ��� ���� �� ����
	InitDib();

	return TRUE;
}

