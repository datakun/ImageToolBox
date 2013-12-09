//////////////////////////////////////////////////////////////////////
//                                                                  //
// Dib.h: header file of the CDib class.                            //
//                                                                  //
// Copyright (c) 2003~<current> Sun-Kyoo Hwang                      //
//                              sunkyoo.ippbook@gmail.com           //
//                                                                  //
// ����ó�� ���α׷��� By Visual C++                                //
//                                                                  //
// Last modified: 10/04/2007                                        //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#pragma once

class RGBBYTE;

class CDib
{
//-----------------------------------------------------------------------------
// ��� ���� ����
//-----------------------------------------------------------------------------

protected:
	LONG        m_nWidth;		// �̹����� ���� ũ��(�ȼ� ����)
	LONG        m_nHeight;		// �̹����� ���� ũ��(�ȼ� ����)
	WORD        m_nBitCount;	// �ȼ��� ��Ʈ ��
	DWORD       m_nDibSize;		// (BITMAPINFOHEADER + ���� ���̺� + �ȼ� ������) ũ��

	BYTE*       m_pDib;			// DIB ������ ��� �ִ� ������ ���� �ּ�

	BYTE**      m_pPtr;			// �׷��̽����� �̹������� 2D �ȼ� ���ٿ� ������
	RGBBYTE**   m_pRgbPtr;		// Ʈ��Į�� �̹������� 2D �ȼ� ���ٿ� ������

//-----------------------------------------------------------------------------
// ��� �Լ� ����
//-----------------------------------------------------------------------------

public:
	// ������ �� �Ҹ���
	CDib(void);
	CDib(const CDib& dib);
	~CDib(void);

	// �̹��� ���� �� �Ҹ�
	BOOL        CreateGrayImage(int nWidth, int nHeight, BYTE value = 255);
	BOOL        CreateRGBImage(int nWidth, int nHeight, COLORREF value = 0x00ffffff);
	void        Destroy();

	// ġȯ ������ �����ε��� �̹��� ���� 
	CDib&       operator=(const CDib& dib);
	BOOL        Copy(CDib* pImage);

	// �̹��� ȭ�� ���
	void        Draw(HDC hDC);
	void        Draw(HDC hDC, int dx, int dy);
	void        Draw(HDC hDC, int dx, int dy, int dw, int dh, DWORD dwRop = SRCCOPY);
	void        Draw(HDC hDC, int dx, int dy, int dw, int dh, 
		             int sx, int sy, int sw, int sh, DWORD dwRop = SRCCOPY);

	// ���� �����
	BOOL        Load(LPCTSTR lpszFileName);
	BOOL        Save(LPCTSTR lpszFileName);

	// 2D �ȼ� �����͸� ��ȯ (�׷��̽����� & Ʈ��Į��)
	BYTE**      GetPtr();
	RGBBYTE**   GetRGBPtr();

	// WIND32 ȯ�濡�� clipboard�� �����ϱ� �Ǵ� �ٿ��ֱ�
	BOOL        CopyToClipboard();
	BOOL        PasteFromClipboard();

	// �̹��� ���� ��ȯ �Լ�
	LONG        GetHeight()	    { return m_nHeight;   }
	LONG        GetWidth()      { return m_nWidth;    }
	WORD        GetBitCount()   { return m_nBitCount; }
	DWORD       GetDibSize()    { return m_nDibSize;  }
	BOOL        IsValid()       { return (m_pDib != NULL); }

	// BITMAPINFOHEADER ���� ������ ��ȯ
	LPBITMAPINFO GetBitmapInfoAddr() { return (LPBITMAPINFO)m_pDib; }

	// �ȷ�Ʈ���� RGBQUAD �迭�� ������ ��ȯ
	int         GetPaletteNums();

	// �ȼ� ������ ���� ������ ��ȯ
	LPVOID      GetDibBitsAddr();

protected:
	// m_pDib ���� ��, �̹��� ���� ���� �Լ�
	BOOL        InitDib();

	// BMP ���� �ҷ�����/�����ϱ�
	BOOL        LoadBMP(LPCTSTR lpszFileName);
	BOOL        SaveBMP(LPCTSTR lpszFileName);

	// 2D �ȼ� ������ ������ ���� �������̽� ���� & �Ҹ�
	BOOL        AllocPtr();
	void        FreePtr();
};

///////////////////////////////////////////////////////////////////////////
// GetPtr, GetRGBPtr ��� �Լ��� �ζ��� �Լ��� ����
///////////////////////////////////////////////////////////////////////////

inline BYTE**    CDib::GetPtr()
{
	ASSERT(m_nBitCount == 8);
	ASSERT(m_pPtr != NULL);

	return m_pPtr;
}

inline RGBBYTE** CDib::GetRGBPtr()
{
	ASSERT(m_nBitCount == 24);
	ASSERT(m_pRgbPtr != NULL);

	return m_pRgbPtr;
}

///////////////////////////////////////////////////////////////////////////
// ���ø� ���� �Լ� ����
///////////////////////////////////////////////////////////////////////////

/*************************************************************************
* 
* �̸� : limit(const T& value)
* ���� : value - ���� Ȥ�� �Ǽ�.
* ��ȯ : 0~255 ������ ��.
* ���� : value ���� 0���� ������ 0����, 255���� ũ�� 255�� �����Ѵ�.
* 
*************************************************************************/

template<typename T>
inline T limit(const T& value)
{
	return ( (value > 255) ? 255 : ((value < 0) ? 0 : value) );
}

/*************************************************************************
* 
* �̸� : limit(const T& value, const T& lower, const T& upper)
* ���� : value - ���� Ȥ�� �Ǽ�.
* ��ȯ : lower ~ upper ������ ��.
* ���� : value ���� lower���� ������ lower����, 
*        upper���� ũ�� upper�� �����Ѵ�.
* 
*************************************************************************/

template<typename T>
inline T limit(const T& value, const T& lower, const T& upper)
{
	return ((value > upper) ? upper : ((value < lower) ? lower : value));
}

/*************************************************************************
* 
* �̸� : swap(T& lha, T& rha)
* ���� : lha - Left hand argument, rha - Right hand argument.
* ��ȯ : ����.
* ���� : rha�� lha�� ���� ���� �ٲ۴�.
* 
*************************************************************************/

template<typename T> 
inline void swap(T& lha, T& rha)
{
	T tmp = lha;
	lha = rha;
	rha = tmp;
}

