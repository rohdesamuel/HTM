#include <stdlib.h>
#include <string.h>

#include "Matrix.h"

void matrixInit(SMtrx* pSMtrx, int nWidth, int nHeight)
{
	int w, h;

	pSMtrx->nWidth = nWidth;
	pSMtrx->nHeight = nHeight;	
	pSMtrx->pSMtrxNodeRow = malloc(nHeight * nWidth * sizeof(SMtrxElmt*));
	pSMtrx->pSMtrxNodeCol = malloc(nHeight * nWidth * sizeof(SMtrxElmt*));

	for (w = 0; w < nWidth; w ++)
		for (h = 0; h < nHeight; h ++)
		{
			pSMtrx->pSMtrxNodeRow[w + (nWidth * h)] = matrixElementCreate(pSMtrx, NULL, w, h);
		}

	for (w = 0; w < nWidth; w ++)
		for (h = 0; h < nHeight; h ++)
		{
			pSMtrx->pSMtrxNodeCol[h + (nHeight * w)] = pSMtrx->pSMtrxNodeRow[w + (nWidth * h)];
		}
}

SMtrxElmt* matrixElementGet(SMtrx* pSMtrx, int nX, int nY)
{
	return pSMtrx->pSMtrxNodeRow[nX + (pSMtrx->nWidth * nY)];
}

void matrixElementInit(SMtrxElmt* pSMtrxElmt, void* data, int nX, int nY)
{
	pSMtrxElmt->data = data;
	pSMtrxElmt->nX = nX;
	pSMtrxElmt->nY = nY;
}

SMtrxElmt* matrixElementCreate(SMtrx* pSMtrx, void* data, int nX, int nY)
{
	SMtrxElmt* pSMtrxElmt = (SMtrxElmt*)malloc(sizeof(SMtrxElmt));
	pSMtrxElmt->data = data;
	pSMtrxElmt->nX = nX;
	pSMtrxElmt->nY = nY;

	return pSMtrxElmt;
}

void matrixAddRow(SMtrx* pSMtrx)
{
	int w, h;
	
	pSMtrx->pSMtrxNodeRow = realloc(pSMtrx->pSMtrxNodeRow, (pSMtrx->nHeight + 1) * pSMtrx->nWidth * sizeof(SMtrxElmt*));

	for (w = 0; w < pSMtrx->nWidth; w ++)
	{
		pSMtrx->pSMtrxNodeRow[w + (pSMtrx->nHeight * pSMtrx->nWidth)] = matrixElementCreate(pSMtrx, NULL, w, pSMtrx->nHeight);
	}

	pSMtrx->nHeight ++;
	free(pSMtrx->pSMtrxNodeCol);
	pSMtrx->pSMtrxNodeCol = malloc(pSMtrx->nWidth * pSMtrx->nHeight * sizeof(SMtrxElmt*));

	for (w = 0; w < pSMtrx->nWidth; w ++)
		for (h = 0; h < pSMtrx->nHeight; h ++)
		{
			pSMtrx->pSMtrxNodeCol[h + (pSMtrx->nHeight * w)] = pSMtrx->pSMtrxNodeRow[w + (pSMtrx->nWidth * h)];
		}
}

void matrixAddColumn(SMtrx* pSMtrx)
{
	int w, h;

	pSMtrx->pSMtrxNodeCol = realloc(pSMtrx->pSMtrxNodeCol, pSMtrx->nHeight * (pSMtrx->nWidth + 1) * sizeof(SMtrxElmt*));	
	
	for (h = 0; h < pSMtrx->nHeight; h ++)
	{
		pSMtrx->pSMtrxNodeCol[h + (pSMtrx->nHeight * pSMtrx->nWidth)] = matrixElementCreate(pSMtrx, NULL, pSMtrx->nWidth, h);
	}

	pSMtrx->nWidth ++;
	free(pSMtrx->pSMtrxNodeRow);
	pSMtrx->pSMtrxNodeRow = malloc(pSMtrx->nWidth * pSMtrx->nHeight * sizeof(SMtrxElmt*));
	
	for (w = 0; w < pSMtrx->nWidth; w ++)
		for (h = 0; h < pSMtrx->nHeight; h ++)
		{
			pSMtrx->pSMtrxNodeRow[w + (pSMtrx->nWidth * h)] = pSMtrx->pSMtrxNodeCol[h + (pSMtrx->nHeight * w)];
		}
}

void matrixDeleteRow(SMtrx* pSMtrx, int nRow)
{
	void* dest;
	void* src;
	int size, w, h;

	dest = pSMtrx->pSMtrxNodeRow + (pSMtrx->nWidth * nRow);
	src = pSMtrx->pSMtrxNodeRow + pSMtrx->nWidth + (pSMtrx->nWidth * nRow);
	size = ((pSMtrx->nWidth * (pSMtrx->nHeight - nRow)) - 1) * sizeof(SMtrxElmt*);
	free(pSMtrx->pSMtrxNodeCol);

	for (w = 0; w < pSMtrx->nWidth; w++)
	{
		free(pSMtrx->pSMtrxNodeRow[(pSMtrx->nWidth * nRow) + w]);
	}
	
	memmove(dest, src, size);
	pSMtrx->nHeight-=1;
	pSMtrx->pSMtrxNodeCol = malloc(pSMtrx->nWidth * pSMtrx->nHeight * sizeof(SMtrxElmt*));
	
	for (w = 0; w < pSMtrx->nWidth; w ++)
		for (h = 0; h < pSMtrx->nHeight; h ++)
		{
			pSMtrx->pSMtrxNodeCol[h + (pSMtrx->nHeight * w)] = pSMtrx->pSMtrxNodeRow[w + (pSMtrx->nWidth * h)];
		}
}

void matrixDeleteColumn(SMtrx* pSMtrx, int nCol)
{
	void* dest;
	void* src;
	int size, w, h;

	dest = pSMtrx->pSMtrxNodeCol + (pSMtrx->nHeight * nCol);
	src = pSMtrx->pSMtrxNodeCol + pSMtrx->nHeight + (pSMtrx->nHeight * nCol);
	size = ((pSMtrx->nHeight * (pSMtrx->nWidth - nCol)) - 1) * sizeof(SMtrxElmt*);
	free(pSMtrx->pSMtrxNodeRow);

	for (h = 0; h < pSMtrx->nHeight; h++)
	{
		free(pSMtrx->pSMtrxNodeCol[(pSMtrx->nHeight * nCol) + h]);
	}
	
	memmove(dest, src, size);
	pSMtrx->nWidth-=1;
	pSMtrx->pSMtrxNodeRow = malloc(pSMtrx->nWidth * pSMtrx->nHeight * sizeof(SMtrxElmt*));
	
	for (w = 0; w < pSMtrx->nWidth; w ++)
		for (h = 0; h < pSMtrx->nHeight; h ++)
		{
			pSMtrx->pSMtrxNodeRow[w + (pSMtrx->nWidth * h)] = pSMtrx->pSMtrxNodeCol[h + (pSMtrx->nHeight * w)];
		}
}
