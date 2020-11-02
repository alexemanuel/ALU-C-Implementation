#include <stdio.h> 
#include <math.h>
#include "ALUFunctions.h"
#include "utils.h"


flags statusFlags = {0, 0, 0};


void slt(int binaryArrayA[], int binaryArrayB[], int *result)
{
	int subtractResult[WORDLENGTH];

	sub(binaryArrayA, binaryArrayB, subtractResult);
	result[WORDLENGTH - 1] = subtractResult[0] | statusFlags.overflowFlag;
}


void checkZeroResult(int binary[])
{
	int isZero = 0;
	int i;

	for(i = WORDLENGTH - 1; i >= 0; i--){
		isZero |= binary[i] | binary[i + 1]; 
	}
	statusFlags.zeroFlag = !isZero;
}


void add(int binaryArrayA[], int binaryArrayB[], int *result)
{
	int carryIn  = 0;	
	int carryOut = 0;
	int i;	

	for(i = WORDLENGTH - 1; i >= 0; i--){
		carryIn = carryOut;
		result[i] = fullAdder(binaryArrayA[i], binaryArrayB[i], carryIn, &carryOut);
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


void sub(int binaryArrayA[], int binaryArrayB[], int *result)
{
	int invertedB[WORDLENGTH];
	int negativeB[WORDLENGTH];
	
	// Represent the value 1 in binary
	int binaryArray1[WORDLENGTH];
	decimalToBinaryArray(WORDLENGTH - 1, 1, binaryArray1);

	// Tow's Complemenlt: First invert the second binary, then add 1
	invert(binaryArrayB, invertedB);
	add(invertedB, binaryArray1, negativeB); 
	
	add(binaryArrayA, negativeB, result);	
}


void and(int binaryArrayA[], int binaryArrayB[], int *result)
{
	int i;	

	for(i = WORDLENGTH - 1; i >= 0; i--){
		result[i] = binaryArrayA[i] & binaryArrayB[i]; 
	}
}


void or(int binaryArrayA[], int binaryArrayB[], int *result)
{
	int i;	

	for(i = WORDLENGTH - 1; i >= 0; i--){
		result[i] = binaryArrayA[i] | binaryArrayB[i]; 
	}
}


void nor(int binaryArrayA[], int binaryArrayB[], int *result)
{
	int orResult[WORDLENGTH];

	// First make OR, then invert the result 
	or(binaryArrayA, binaryArrayB, orResult);
	invert(orResult, result);
}


void invert(int binary[], int *result)
{
	int i;	

	for(i = WORDLENGTH - 1; i >= 0; i--){
		result[i] = binary[i] ^ 1; 
	}	
}


void xor(int binaryArrayA[], int binaryArrayB[], int *result)
{
	int i;	
	
	for(i = WORDLENGTH - 1; i >= 0; i--){
		result[i] = binaryArrayA[i] ^ binaryArrayB[i]; 
	}
}

flags getStatusFlags()
{
	return statusFlags;
}


