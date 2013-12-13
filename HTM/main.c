#include <stdio.h>
#include <stdlib.h>

#include "ConsoleDraw.h"
#include "Matrix.h"

void AHC_startf(SMtrx* pSMtrx);

int main(void)
{
	int w, h;
	float* fRand;

	SMtrx pSMtrx;
	SMtrxElmt* pSMtrxElmt;
	HANDLE hCD;

	hCD = CD_CreateWindow(0,0,50,20);
	CD_Refresh(hCD);
	

	matrixInit(&pSMtrx, 10, 10);

	for (w = 0; w < pSMtrx.nWidth; w ++)
		for (h = 0; h < pSMtrx.nHeight; h ++)
		{
			fRand = malloc(sizeof(float));
			*fRand = (float)(rand() % 100000)/100000;
			pSMtrxElmt = matrixElementGet(&pSMtrx, w, h);
			pSMtrxElmt->data = fRand;
			CD_SetBufferChar(hCD, w * 2, h, w + (h * pSMtrx.nHeight), CD_FG_WHITE);
		}
	AHC_startf(&pSMtrx);
	CD_DrawScreen(hCD);

	while(1){}
	return 0;
}


void AHC_startf(SMtrx* pSMtrx)
{
	SMtrxElmt *pSMtrxElmt;
	int w, h, i, nU, nV, nWidth, nHeight;
	float fDataMin, fData;
	float *pfData;

	w = h= 0;
	nU = nV = 0;

	fDataMin = 0;
	fData = 0;

	nWidth = pSMtrx->nWidth;
	nHeight = pSMtrx->nHeight;
	while(nWidth > 0)
	{
		fDataMin = *((float*)pSMtrx->pSMtrxNodeRow[1]->data);
		//First element is always Zero
		for (w = 2; w < nWidth; w ++)
		{
			fData = *((float*)pSMtrx->pSMtrxNodeRow[w]->data);
			if (fData < fDataMin)
			{
				fDataMin = fData;
				nU = 0;
				nV = w;
			}
		}

		matrixAddRow(pSMtrx);
		matrixAddColumn(pSMtrx);

		//Last element is always 0
		for (i = 0; i < nWidth - 1; i++)
		{
			pfData = malloc(sizeof(float));
			*pfData = *(MATRIX_DATA(pSMtrx,0,i,float*)) - fDataMin;
			pSMtrx->pSMtrxNodeCol[i + ((nHeight - 1) * nWidth)]->data = pfData;
			pSMtrx->pSMtrxNodeRow[i + ((nHeight - 1) * nWidth)]->data = pfData;
		}


		pfData = malloc(sizeof(float));
		*pfData = 0.0f;

		//Last element is always 0
		pSMtrx->pSMtrxNodeCol[nWidth - 1]->data = pfData;
		pSMtrx->pSMtrxNodeRow[nWidth - 1]->data = pfData;
		
		nWidth --;
		nHeight --;
		matrixDeleteRow(pSMtrx, nV);
		matrixDeleteColumn(pSMtrx, nV);
		if (nV != 0)
		{
			nWidth --;
			nHeight --;
			matrixDeleteRow(pSMtrx, 0);
			matrixDeleteColumn(pSMtrx, 0);
		}
	}
}