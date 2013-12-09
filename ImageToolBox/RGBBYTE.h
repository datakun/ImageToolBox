//////////////////////////////////////////////////////////////////////
//                                                                  //
// RGBBYTE.h: interface for the RGBBYTE class.                      //
//                                                                  //
// Copyright (c) 2003~<current> Sun-Kyoo Hwang                      //
//                              sunkyoo.ippbook@gmail.com           //
//                                                                  //
// ����ó�� ���α׷��� By Visual C++                                  //
//                                                                  //
// Last modified: 10/04/2007                                        //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#pragma once

class RGBBYTE  
{
//-----------------------------------------------------------------------------
// ��� ���� ����
//-----------------------------------------------------------------------------

public:
	BYTE b;
	BYTE g;
	BYTE r;

//-----------------------------------------------------------------------------
// ��� �Լ� ����
//-----------------------------------------------------------------------------

public:
	RGBBYTE(const BYTE& pixel = 0);     // �⺻ ������
	RGBBYTE(const BYTE& _r, const BYTE& _g, const BYTE& _b);
	RGBBYTE(const RGBBYTE& pixel);      // ���� ������
	~RGBBYTE();							// �Ҹ���

public:
	// ġȯ ������ �����ε�
	RGBBYTE&    operator=(const RGBBYTE& pixel);
	RGBBYTE&    operator=(const COLORREF& pixel);
	RGBBYTE&    operator=(const BYTE& pixel);

	// ���� ������ �����ε�
	int         operator==(const RGBBYTE& pixel);
	int         operator!=(const RGBBYTE& pixel);
};

