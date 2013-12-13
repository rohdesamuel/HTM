#include <stdio.h>
#include <stdlib.h>

#include "Node.h"

void nodeInit(SNode* pSNode)
{
	pSNode->enMode = LEARN;
	pSNode->enState = FALSE;

	pSNode->nSNode = 0;
	pSNode->nSPtrn = 0;

}

void ptrnInit(SPtrn* pSPtrn)
{
	pSPtrn->cInput = 0x00000000; //Going to use an 8 bit input

	pSPtrn->nSPtrnIn = 0;
	pSPtrn->nSPtrnOut = 0;

}

void nodeLink(SNode* pSNode, SNode* pSNodeIn)
{
	pSNode->pSNodeIn[pSNode->nSNode] = pSNodeIn;
	pSNode->nSNode ++;
}

SPtrn* nodeAddPtrn(SNode* pSNode)
{
	int i;
	SPtrn* pSPtrn = (SPtrn*)malloc(sizeof(SPtrn));

	if (pSPtrn == NULL)
		printf("ERROR");
	
	ptrnInit(pSPtrn);

	for (i = 0; i < pSNode->nSNode; i ++)
	{
		pSPtrn->cInput += pSNode->pSNodeIn[i]->enState;
		
		if (i < pSNode->nSNode - 1)
			pSPtrn->cInput <<= 1;
	}

	pSNode->rgpSPtrn[pSNode->nSPtrn] = pSPtrn;
	pSNode->nSPtrn ++;

	return pSPtrn;
}