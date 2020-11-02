#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define WORDLENGTH 5

struct flags {
	unsigned int zeroFlag : 1;
	unsigned int overflowFlag : 1;
	unsigned int carryFlag : 1;
}statusFlags;

enum operationCodes {ADD, SUB, AND, OR, NOR, SLT, XOR};

int halfAdder(int bitA, int bitB, int *carryOut);

int fullAdder(int bitA, int bitB, int carryIn, int *carryOut);

void add(int binaryA[], int binaryB[], int *result);

void sub(int binaryA[], int binaryB[], int *result);

void and(int binaryA[], int binaryB[], int *result);

void or(int binaryA[], int binaryB[], int *result);

void nor(int binary[], int binaryB[], int *result);

void xor(int binaryA[], int binaryB[], int *result);

void checkZeroResult(int binary[]);

void slt(int binaryA[], int binaryB[], int *result);

void invert(int binary[], int *result);

void getBinaryFromFile(FILE* file, char* binaryArray);

int binaryToDecimal(char binary[]);

void binaryToDecimalArray(char binary[], int *binaryDecimalArray);

void printResult(int binaryOutput[]);


int main()
{
	FILE *pointerInputFile;
	pointerInputFile = fopen("inputs.txt", "r");

	if(pointerInputFile == NULL){
		printf("Can not open the file");
		return 1;
	}

	char binarya[WORDLENGTH], binaryb[WORDLENGTH];
	getBinaryFromFile(pointerInputFile, binarya);
	getBinaryFromFile(pointerInputFile, binaryb);

	int binaryA[WORDLENGTH], binaryB[WORDLENGTH];
	binaryToDecimalArray(binarya, binaryA);
	binaryToDecimalArray(binaryb, binaryB);

	char binaryOp[WORDLENGTH]; 
	getBinaryFromFile(pointerInputFile, binaryOp);
	int opCode = binaryToDecimal(binaryOp);

	int binaryResult[] = {0, 0, 0, 0, 0};

	switch(opCode){

		case ADD:
			add(binaryA, binaryB, binaryResult);
			break;

		case SUB:
			sub(binaryA, binaryB, binaryResult);
			break;

		case AND:
			and(binaryA, binaryB, binaryResult);
			break;

		case OR:
			or(binaryA, binaryB, binaryResult);
			break;

		case NOR:
			nor(binaryA, binaryB, binaryResult);
			break;

		case SLT:
			slt(binaryA, binaryB, binaryResult);
			break;

		case XOR:
			xor(binaryA, binaryB, binaryResult);
			break;
	}

	checkZeroResult(binaryResult);
	printResult(binaryResult);
	
	return 0;
}

void printResult(int binaryOutput[])
{
	printf("===================================\n");
	printf("Output Binary: ");
	
	for(int i = 0; i < WORDLENGTH; i++){
		printf("%d", binaryOutput[i]);
	}

	printf("\n");

	printf("Flags:\n");
	printf("Zero Flag     %d\n", statusFlags.zeroFlag);
	printf("OverFlow Flag %d\n", statusFlags.overflowFlag);
	printf("Carry Flag    %d\n", statusFlags.carryFlag);
	printf("===================================\n");
}


void binaryToDecimalArray(char binaryString[], int *binaryDecimalArray)
{
	for(int i = WORDLENGTH - 1; i >= 0; i--){
		binaryDecimalArray[i] = binaryString[i] == '1';
	}
}


int binaryToDecimal(char binary[])
{
	int decimal = 0;

	for(int i = WORDLENGTH -1; i >= 0; i--){
		decimal += pow(2, WORDLENGTH - 1 - i) * (binary[i] == '1');
	}
	return decimal;
}


void getBinaryFromFile(FILE *file, char *binaryArray) 
{
	fgets(binaryArray, WORDLENGTH + 1, file);
	fgetc(file); //Skip blank space
}


void slt(int binaryA[], int binaryB[], int *result)
{
	int subtractResult[WORDLENGTH];

	sub(binaryA, binaryB, subtractResult);
	result[WORDLENGTH - 1] = subtractResult[0] | statusFlags.overflowFlag;
}


void checkZeroResult(int binary[]){
	int isZero = 0;

	for(int i = WORDLENGTH - 1; i >= 0; i--){
		isZero |= binary[i] | binary[i + 1]; 
	}
	statusFlags.zeroFlag = !isZero;
}


void add(int binaryA[], int binaryB[], int *result){
	int carryIn  = 0;	
	int carryOut = 0;

	for(int i = WORDLENGTH - 1; i >= 0; i--){
		carryIn = carryOut;
		result[i] = fullAdder(binaryA[i], binaryB[i], carryIn, &carryOut);
	}

	statusFlags.overflowFlag = carryIn | carryOut;
	statusFlags.carryFlag = carryOut;
}


int halfAdder(int bitA, int bitB, int *carryOut)
{
	int result = bitA ^ bitB;
	*carryOut = bitA & bitB;

	return result;
}


int fullAdder(int bitA, int bitB, int carryIn, int *carryOut)
{
	int carryOutSumAB;
	int carryOutSumABCarryIn;

	int sumAB = halfAdder(bitA, bitB, &carryOutSumAB);
	int result = halfAdder(sumAB, carryIn, &carryOutSumABCarryIn);

	*carryOut = carryOutSumAB | carryOutSumABCarryIn; 

	return result;	
}


void sub(int binaryA[], int binaryB[], int *result)
{
	int invertedB[WORDLENGTH];
	int negativeB[WORDLENGTH];

	int array1[] = {0, 0, 0, 0, 1};

	// Tow's Complement
	invert(binaryB, invertedB);
	add(invertedB, array1, negativeB); 
	
	add(binaryA, negativeB, result);	
}


void and(int binaryA[], int binaryB[], int *result)
{
	for(int i = WORDLENGTH - 1; i >= 0; i--){
		result[i] = binaryA[i] & binaryB[i]; 
	}
}


void or(int binaryA[], int binaryB[], int *result)
{
	for(int i = WORDLENGTH - 1; i >= 0; i--){
		result[i] = binaryA[i] | binaryB[i]; 
	}
}


void nor(int binaryA[], int binaryB[], int *result)
{
	int orResult[WORDLENGTH];
	or(binaryA, binaryB, orResult);

	invert(orResult, result);
}


void invert(int binary[], int *result){
	
	for(int i = WORDLENGTH - 1; i >= 0; i--){
		result[i] = binary[i] ^ 1; 
	}	
}


void xor(int binaryA[], int binaryB[], int *result)
{
	for(int i = WORDLENGTH - 1; i >= 0; i--){
		result[i] = binaryA[i] ^ binaryB[i]; 
	}
}


