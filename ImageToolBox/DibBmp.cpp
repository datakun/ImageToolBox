//////////////////////////////////////////////////////////////////////
//                                                                  //
// DibBmp.cpp: implementation of the CDib class.                    //
//                                                                  //
// Copyright (c) 2003~<current> Sun-Kyoo Hwang                      //
//                              sunkyoo.ippbook@gmail.com           //
//                                                                  //
// 영상처리 프로그래밍 By Visual C++                                //
//                                                                  //
// Last modified: 10/04/2007                                        //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dib.h"

#define DIB_HEADER_MARKER ((WORD) ('M' << 8) | 'B')

/*************************************************************************
typedef struct tagBITMAPFILEHEADER { // bmfh 
	WORD    bfType;			// 비트맵을 표시 (항상 "BM")
	DWORD   bfSize;			// 전체 파일 크기
	WORD    bfReserved1;	// 예약된 값. 항상 0
	WORD    bfReserved2;	// 예약된 값. 항상 0
	DWORD   bfOffBits;		// BITMAPFILEHEADER에서 픽셀 데이터까지의 옵셋
} BITMAPFILEHEADER; 

typedef struct tagBITMAPINFOHEADER{ // bmih 
	DWORD  biSize;			// 이 구조체의 크기
	LONG   biWidth;			// 이미지의 폭 (픽셀 단위)
	LONG   biHeight;		// 이미지의 높이 (픽셀 단위)
	WORD   biPlanes;		// 비트플레인 수 (항상 1)
	WORD   biBitCount		// 픽셀 당 비트 수
	DWORD  biCompression;	// 압축 유형
	DWORD  biSizeImage;		// 픽셀 데이터의 크기(바이트 수)
	LONG   biXPelsPerMeter;	// 가로 해상도
	LONG   biYPelsPerMeter; // 세로 해상도
	DWORD  biClrUsed;		// 실제 사용되는 색상 수
	DWORD  biClrImportant;	// 중요한 색상 인덱스 (0이면 전체)
} BITMAPINFOHEADER; 
*************************************************************************/

/*************************************************************************
* 
* 이름 : LoadBMP(LPCTSTR lpszFileName)
* 인자 : lpszFileName - 파일의 전체 경로 이름.
* 반환 : 성공하면 TRUE, 실패하면 FALSE를 반환.
* 설명 : BMP 파일을 읽어서 CDib 객체를 생성한다.
* 
*************************************************************************/

BOOL CDib::LoadBMP(LPCTSTR lpszFileName)
{
	CFile   file;
	UINT    nFileSize, nDibSize;

	BITMAPFILEHEADER    bmfh;
	LPBITMAPINFOHEADER  lpbmi;

	// 읽기 모드로 파일 열기
	if( !file.Open(lpszFileName, CFile::modeRead | CFile::shareDenyWrite) )
		return FALSE;

	// BMP 파일의 크기 (바이트 단위)
	nFileSize = (UINT)file.GetLength();

	// BITMAPFILEHEADER 읽기
	if( file.Read((LPSTR)&bmfh, sizeof(BITMAPFILEHEADER)) 
		!= sizeof(BITMAPFILEHEADER) )
	{
		file.Close();
		return FALSE;
	}

	// BMP 파일임을 나타내는 "BM" 마커가 있는지 확인
	if( bmfh.bfType != DIB_HEADER_MARKER )
	{
		file.Close();
		return FALSE;
	}

	// Packed-DIB 메모리 블럭의 크기 계산
	nDibSize = nFileSize - sizeof(bmfh);

	// 현재 설정된 CDib 객체가 있다면 삭제한다.
	if( m_pDib ) Destroy();

	// 위에서 계산한 만큼의 메모리 할당
	m_pDib = new BYTE[nDibSize];
	if( m_pDib == NULL ) 
	{
		file.Close();
		return FALSE;
	}

	// 파일로부터 Packed-DIB 크기만큼을 읽기
	if( file.Read(m_pDib, nDibSize) != nDibSize ) 
	{
		delete [] m_pDib;
		m_pDib = NULL;
		file.Close();
		return FALSE;
	}

	// BITMAPINFOHEADER 버전을 확인한다. 
	lpbmi = (LPBITMAPINFOHEADER)m_pDib;
	if( lpbmi->biSize != sizeof(BITMAPINFOHEADER) )
	{
		delete [] m_pDib;
		m_pDib = NULL;
		file.Close();
		return FALSE;
	}

	// 이제 m_pDib는 DIB를 담고있는 버퍼의 시작 주소를 가리키고 있다. 
	// CDib 클래스의 멤버 변수의 값을 설정한다.
	if( !InitDib() )
	{
		delete [] m_pDib;
		m_pDib = NULL;
		file.Close();
		return FALSE;
	}

	// 파일 닫기
	file.Close();

	return TRUE;
}

/*************************************************************************
* 
* 이름 : LoadBMP(LPCTSTR lpszFileName)
* 인자 : lpszFileName - 파일의 전체 경로 이름.
* 반환 : 성공하면 TRUE, 실패하면 FALSE를 반환.
* 설명 : CDib 객체를 BMP 파일 형식으로 저장한다.
* 
*************************************************************************/

BOOL CDib::SaveBMP(LPCTSTR lpszFileName)
{
	CFile	file;
	BITMAPFILEHEADER    bmfh;

	// DIB 객체를 포함하고 있지 않으면 FALSE를 반환.
	if( m_pDib == NULL )
		return FALSE;

	// 쓰기 모드로 파일 열기
	if( !file.Open(lpszFileName, CFile::modeCreate | CFile::modeWrite | 
		CFile::shareDenyWrite) )
		return FALSE;

	// BITMAPFILEHEADER 멤버 변수 설정
	bmfh.bfType      = DIB_HEADER_MARKER;	// 항상 "BM"
	bmfh.bfSize		 = (DWORD)sizeof(BITMAPFILEHEADER) + m_nDibSize;
	bmfh.bfReserved1 = 0;		// 항상 0
	bmfh.bfReserved2 = 0;		// 항상 0
	bmfh.bfOffBits	 = (DWORD)(sizeof(BITMAPFILEHEADER) 
		+ sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*GetPaletteNums());

	// BITMAPFILEHEADER 쓰기 
	file.Write((LPSTR)&bmfh, sizeof(bmfh));

	// DIB 구조(BITMAPINFOHEADER + 색상 테이블 + 픽셀 데이터) 쓰기
	file.Write(m_pDib, m_nDibSize);

	// 파일 닫기
	file.Close();

	return TRUE;
}
