#include "StdAfx.h"
#include "Dib.h"
#include "DibEnhancement.h"

#include <math.h>

void DibInverse(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	for (j = 0; j < h; j++)
	for (i = 0; i < w; i++)
	{
		ptr[j][i] = 255 - ptr[j][i];
	}
}

void DibBrightness(CDib& dib, int n)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	for (j = 0; j < h; j++)
	for (i = 0; i < w; i++)
	{
		ptr[j][i] = limit(ptr[j][i] + n);
	}
}

void DibContrast(CDib& dib, int n)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	BYTE value;
	for (j = 0; j < h; j++)
	for (i = 0; i < w; i++)
	{
		value = ptr[j][i];
		ptr[j][i] = limit(value + ((value - 128) * n / 100));
	}
}

void DibGammaCorrection(CDib& dib, float gamma)
{
	register int i, j;
	float invgamma = 1.f / gamma;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	for (j = 0; j < h; j++)
	for (i = 0; i < w; i++)
	{
		ptr[j][i] = (BYTE)limit(pow((ptr[j][i] / 255.f), invgamma) * 255 + 0.5f);
	}
}

void DibHistogram(CDib& dib, float histo[256])
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	// 히스토그램 계산

	int temp[256];
	memset(temp, 0, sizeof(int)* 256);
	for (j = 0; j < h; j++)
	for (i = 0; i < w; i++)
	{
		temp[ptr[j][i]]++;
	}

	// 히스토그램 정규화(histogram normalization)

	float area = (float)w*h;
	for (i = 0; i < 256; i++)
		histo[i] = temp[i] / area;
}

void DibHistEqual(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	// 히스토그램 계산

	float hist[256];
	DibHistogram(dib, hist);

	// 히스토그램 누적 함수 계산

	double cdf[256] = { 0.0, };
	cdf[0] = hist[0];
	for (i = 1; i < 256; i++)
		cdf[i] = cdf[i - 1] + hist[i];

	// 히스토그램 균등화

	BYTE** ptr = dib.GetPtr();

	for (j = 0; j < h; j++)
	for (i = 0; i < w; i++)
	{
		ptr[j][i] = (BYTE)limit(cdf[ptr[j][i]] * 255);
	}
}
