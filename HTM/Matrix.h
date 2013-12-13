#pragma once

#ifndef MATRIX__H
#define MATRIX__H

/*Get matrix data*/
#define MATRIX_DATA(pSMtrx, x, y, type) \
	((type) ((pSMtrx)->pSMtrxNodeRow[ ((pSMtrx)->nWidth) * (y) + (x) ]->data))

/*Matrix Definition*/
typedef struct SMtrx {
		int nWidth, nHeight;
		struct SMtrxElmt** pSMtrxNodeRow;
		struct SMtrxElmt** pSMtrxNodeCol;
		} SMtrx;

/*Matrix Element Definition*/
typedef struct SMtrxElmt {
		void* data;
		int nX, nY;
		}SMtrxElmt;

void matrixInit(SMtrx* pSMtrx,int nWidth, int nHeight);
SMtrxElmt* matrixElementCreate(SMtrx* pSMtrx, void* data, int nX, int nY);
SMtrxElmt* matrixElementGet(SMtrx* pSMtrx, int nX, int nY);
void matrixElementInit(SMtrxElmt* pSMtrxElmt, void* data, int nX, int nY);
void matrixDeleteColumn(SMtrx* pSMtrx, int nRow);
void matrixDeleteRow(SMtrx* pSMtrx, int nRow);
void matrixAddColumn(SMtrx* pSMtrx);
void matrixAddRow(SMtrx* pSMtrx);
#endif