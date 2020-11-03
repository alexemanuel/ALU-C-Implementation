#include <stdio.h>
#include "ALUFunctions.h"
#include "utils.h"


enum operationCodes {ADD, SUB, AND, OR, NOR, SLT, XOR};
char operaions[7][4] = {"add", "sub", "AND", "OR", "NOR", "slt", "XOR"};

int main()
{
	FILE *ptrInputFile;
	ptrInputFile = fopen("inputs.txt", "r");

	if(ptrInputFile == NULL){
		printf("Can not open the file");
		return 1;
	}

	// Get the 32-bit value from the file.
	char binaryStringA[WORD_LENGTH], binaryStringB[WORD_LENGTH];
	getBinaryStringFromFile(ptrInputFile, binaryStringA, WORD_LENGTH);
	getBinaryStringFromFile(ptrInputFile, binaryStringB, WORD_LENGTH);

	// Transform the char array into int array 
	int binaryArrayA[WORD_LENGTH], binaryArrayB[WORD_LENGTH];
	binaryStringToBinaryArray(binaryStringA, binaryArrayA);
	binaryStringToBinaryArray(binaryStringB, binaryArrayB);

	char binaryOperation[WORD_OPTION_LENGTH]; 
	getBinaryStringFromFile(ptrInputFile, binaryOperation, WORD_OPTION_LENGTH);
	int operationCode = binaryStringToDecimal(binaryOperation);

	int binaryResult[WORD_LENGTH];
	decimalToBinaryArray(WORD_LENGTH - 1, 0, binaryResult);

	switch(operationCode){

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

		default:
			printf("Invalid Operation\n");
			return 0;
	}
	
	checkZeroResult(binaryResult);

	flags statusFlags = getStatusFlags();
	printResult(binaryArrayA, binaryArrayB, binaryResult, operaions[operationCode], statusFlags);
	
	return 0;
}

