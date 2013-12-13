#pragma once

#ifndef NODE__H
#define NODE__H

#define MAX_PTRNS 8
#define MAX_NODES 8

typedef enum {FALSE, TRUE} BOOL;
typedef enum {LEARN, OUTPUT} MODE;

typedef struct SNode
{
	MODE enMode;
	BOOL enState;

	//List of patterns
	struct SPtrn* rgpSPtrn[MAX_PTRNS];
	int nSPtrn;

	//List of all nodes going into this Node
	struct SNode* pSNodeIn[MAX_NODES];
	int nSNode;

} SNode;


typedef struct SPtrn
{
	//Patterns linking into this pattern
	struct SPtrn* pSPtrnIn[MAX_PTRNS];
	int nSPtrnIn;

	//Patterns linking out of this pattern
	struct SPtrn* pSPtrnOut[MAX_PTRNS];
	int nSPtrnOut;

	//The stored input
	char cInput;

	//These numbers are used for the markov graph
	int prgnCountIn[MAX_PTRNS];
	int prgnCountOut[MAX_PTRNS];

	float prgfNormal[MAX_PTRNS];

} SPtrn;

void nodeInit(SNode* pSNode);
void ptrnInit(SPtrn* pSPattern);

void nodeLink(SNode* pSNode, SNode* pSNodeOut);
SPtrn* nodeAddPtrn(SNode* pSNode);

#endif