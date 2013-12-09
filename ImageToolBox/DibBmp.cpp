//////////////////////////////////////////////////////////////////////
//                                                                  //
// DibBmp.cpp: implementation of the CDib class.                    //
//                                                                  //
// Copyright (c) 2003~<current> Sun-Kyoo Hwang                      //
//                              sunkyoo.ippbook@gmail.com           //
//                                                                  //
// ����ó�� ���α׷��� By Visual C++                                //
//                                                                  //
// Last modified: 10/04/2007                                        //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dib.h"

#define DIB_HEADER_MARKER ((WORD) ('M' << 8) | 'B')

/*************************************************************************
typedef struct tagBITMAPFILEHEADER { // bmfh 
	WORD    bfType;			// ��Ʈ���� ǥ�� (�׻� "BM")
	DWORD   bfSize;			// ��ü ���� ũ��
	WORD    bfReserved1;	// ����� ��. �׻� 0
	WORD    bfReserved2;	// ����� ��. �׻� 0
	DWORD   bfOffBits;		// BITMAPFILEHEADER���� �ȼ� �����ͱ����� �ɼ�
} BITMAPFILEHEADER; 

typedef struct tagBITMAPINFOHEADER{ // bmih 
	DWORD  biSize;			// �� ����ü�� ũ��
	LONG   biWidth;			// �̹����� �� (�ȼ� ����)
	LONG   biHeight;		// �̹����� ���� (�ȼ� ����)
	WORD   biPlanes;		// ��Ʈ�÷��� �� (�׻� 1)
	WORD   biBitCount		// �ȼ� �� ��Ʈ ��
	DWORD  biCompression;	// ���� ����
	DWORD  biSizeImage;		// �ȼ� �������� ũ��(����Ʈ ��)
	LONG   biXPelsPerMeter;	// ���� �ػ�
	LONG   biYPelsPerMeter; // ���� �ػ�
	DWORD  biClrUsed;		// ���� ���Ǵ� ���� ��
	DWORD  biClrImportant;	// �߿��� ���� �ε��� (0�̸� ��ü)
} BITMAPINFOHEADER; 
*************************************************************************/

/*************************************************************************
* 
* �̸� : LoadBMP(LPCTSTR lpszFileName)
* ���� : lpszFileName - ������ ��ü ��� �̸�.
* ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
* ���� : BMP ������ �о CDib ��ü�� �����Ѵ�.
* 
*************************************************************************/

BOOL CDib::LoadBMP(LPCTSTR lpszFileName)
{
	CFile   file;
	UINT    nFileSize, nDibSize;

	BITMAPFILEHEADER    bmfh;
	LPBITMAPINFOHEADER  lpbmi;

	// �б� ���� ���� ����
	if( !file.Open(lpszFileName, CFile::modeRead | CFile::shareDenyWrite) )
		return FALSE;

	// BMP ������ ũ�� (����Ʈ ����)
	nFileSize = (UINT)file.GetLength();

	// BITMAPFILEHEADER �б�
	if( file.Read((LPSTR)&bmfh, sizeof(BITMAPFILEHEADER)) 
		!= sizeof(BITMAPFILEHEADER) )
	{
		file.Close();
		return FALSE;
	}

	// BMP �������� ��Ÿ���� "BM" ��Ŀ�� �ִ��� Ȯ��
	if( bmfh.bfType != DIB_HEADER_MARKER )
	{
		file.Close();
		return FALSE;
	}

	// Packed-DIB �޸� ���� ũ�� ���
	nDibSize = nFileSize - sizeof(bmfh);

	// ���� ������ CDib ��ü�� �ִٸ� �����Ѵ�.
	if( m_pDib ) Destroy();

	// ������ ����� ��ŭ�� �޸� �Ҵ�
	m_pDib = new BYTE[nDibSize];
	if( m_pDib == NULL ) 
	{
		file.Close();
		return FALSE;
	}

	// ���Ϸκ��� Packed-DIB ũ�⸸ŭ�� �б�
	if( file.Read(m_pDib, nDibSize) != nDibSize ) 
	{
		delete [] m_pDib;
		m_pDib = NULL;
		file.Close();
		return FALSE;
	}

	// BITMAPINFOHEADER ������ Ȯ���Ѵ�. 
	lpbmi = (LPBITMAPINFOHEADER)m_pDib;
	if( lpbmi->biSize != sizeof(BITMAPINFOHEADER) )
	{
		delete [] m_pDib;
		m_pDib = NULL;
		file.Close();
		return FALSE;
	}

	// ���� m_pDib�� DIB�� ����ִ� ������ ���� �ּҸ� ����Ű�� �ִ�. 
	// CDib Ŭ������ ��� ������ ���� �����Ѵ�.
	if( !InitDib() )
	{
		delete [] m_pDib;
		m_pDib = NULL;
		file.Close();
		return FALSE;
	}

	// ���� �ݱ�
	file.Close();

	return TRUE;
}

/*************************************************************************
* 
* �̸� : LoadBMP(LPCTSTR lpszFileName)
* ���� : lpszFileName - ������ ��ü ��� �̸�.
* ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
* ���� : CDib ��ü�� BMP ���� �������� �����Ѵ�.
* 
*************************************************************************/

BOOL CDib::SaveBMP(LPCTSTR lpszFileName)
{
	CFile	file;
	BITMAPFILEHEADER    bmfh;

	// DIB ��ü�� �����ϰ� ���� ������ FALSE�� ��ȯ.
	if( m_pDib == NULL )
		return FALSE;

	// ���� ���� ���� ����
	if( !file.Open(lpszFileName, CFile::modeCreate | CFile::modeWrite | 
		CFile::shareDenyWrite) )
		return FALSE;

	// BITMAPFILEHEADER ��� ���� ����
	bmfh.bfType      = DIB_HEADER_MARKER;	// �׻� "BM"
	bmfh.bfSize		 = (DWORD)sizeof(BITMAPFILEHEADER) + m_nDibSize;
	bmfh.bfReserved1 = 0;		// �׻� 0
	bmfh.bfReserved2 = 0;		// �׻� 0
	bmfh.bfOffBits	 = (DWORD)(sizeof(BITMAPFILEHEADER) 
		+ sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*GetPaletteNums());

	// BITMAPFILEHEADER ���� 
	file.Write((LPSTR)&bmfh, sizeof(bmfh));

	// DIB ����(BITMAPINFOHEADER + ���� ���̺� + �ȼ� ������) ����
	file.Write(m_pDib, m_nDibSize);

	// ���� �ݱ�
	file.Close();

	return TRUE;
}
