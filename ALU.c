#include <stdio.h>
#include "ALUFunctions.h"
#include "utils.h"


enum operationCodes {ADD, SUB, AND, OR, NOR, SLT, XOR};
char operaions[7][4] = {"add", "sub", "AND", "OR", "NOR", "slt", "XOR"};

int main()
{
	FILE *pointerInputFile;
	pointerInputFile = fopen("inputs.txt", "r");

	if(pointerInputFile == NULL){
		printf("Can not open the file");
		return 1;
	}

	char binaryStringA[WORDLENGTH], binaryStringB[WORDLENGTH];
	getBinaryFromFile(pointerInputFile, binaryStringA, WORDLENGTH);
	getBinaryFromFile(pointerInputFile, binaryStringB, WORDLENGTH);

	int binaryArrayA[WORDLENGTH], binaryArrayB[WORDLENGTH];
	binaryToDecimalArray(binaryStringA, binaryArrayA);
	binaryToDecimalArray(binaryStringB, binaryArrayB);

	char binaryOp[WORDFLAGLENGTH]; 
	getBinaryFromFile(pointerInputFile, binaryOp, WORDFLAGLENGTH);
	int opCode = binaryToDecimal(binaryOp);

	int binaryResult[WORDLENGTH];
	decimalToBinaryArray(WORDLENGTH - 1, 0, binaryResult);

	switch(opCode){

		case ADD:
			add(binaryArrayA, binaryArrayB, binaryResult);
			break;

		case SUB:
			sub(binaryArrayA, binaryArrayB, binaryResult);
			break;

		case AND:
			and(binaryArrayA, binaryArrayB, binaryResult);
			break;

		case OR:
			or(binaryArrayA, binaryArrayB, binaryResult);
			break;

		case NOR:
			nor(binaryArrayA, binaryArrayB, binaryResult);
			break;

		case SLT:
			slt(binaryArrayA, binaryArrayB, binaryResult);
			break;

		case XOR:
			xor(binaryArrayA, binaryArrayB, binaryResult);
			break;
	}
	
	checkZeroResult(binaryResult);

	flags statusFlags = getStatusFlags();
	printResult(binaryArrayA, binaryArrayB, binaryResult, operaions[opCode], statusFlags);
	
	return 0;
}

