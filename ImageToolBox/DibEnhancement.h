#pragma once

void DibInverse(CDib& dib);
void DibBrightness(CDib& dib, int n);
void DibContrast(CDib& dib, int n);
void DibGammaCorrection(CDib& dib, float gamma);
void DibHistogram(CDib& dib, float histo[256]);
void DibHistEqual(CDib& dib);
