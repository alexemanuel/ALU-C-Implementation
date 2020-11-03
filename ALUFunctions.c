#include <stdio.h> 
#include <math.h>
#include "ALUFunctions.h"
#include "utils.h"


flags statusFlags = {0, 0, 0};


void slt(int binaryArrayA[], int binaryArrayB[], int *binaryArrayResult)
{
	int isLessThan;
	int i;

	// Check if the signal bits (most significant) are different
	if(binaryArrayA[0] ^ binaryArrayB[0]){
		// If the most significant bit of A is 1, it means that A is less than B
		isLessThan = binaryArrayA[0];
		
	}else{
		// Start in the next bit after the signal bit
		for(i  = 1; i < WORD_LENGTH; i++){
			if(binaryArrayA[i] ^ binaryArrayB[i]){
				isLessThan = !binaryArrayA[i];
				break;
			}
		}
	}
	// Put the isLessThan value in the least significant bit, returning 0 or 1
	binaryArrayResult[WORD_LENGTH - 1] = isLessThan; 
}


void checkZeroResult(int binary[])
{
	int isZero = 0;
	int i;

	for(i = WORD_LENGTH - 1; i >= 0; i--){
		// Compare the current bit with the next bit
		isZero |= binary[i] | binary[i + 1]; 
	}
	// If all the bits are igual to zero, then zeroFlag is true
	statusFlags.zeroFlag = !isZero;
}


void add(int binaryArrayA[], int binaryArrayB[], int *binaryArrayResult)
{
	int carryIn  = 0;	
	int carryOut = 0;
	int i;	

	for(i = WORD_LENGTH - 1; i >= 0; i--){
		// The next carryIn is the previous carryOut
		carryIn = carryOut;
		binaryArrayResult[i] = fullAdder(binaryArrayA[i], binaryArrayB[i], carryIn, &carryOut);
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


void sub(int binaryArrayA[], int binaryArrayB[], int *binaryArrayResult)
{
	int invertedBinaryB[WORD_LENGTH];
	int negativeBinaryB[WORD_LENGTH];
	
	// Represent the value 1 in binary
	int binaryArray1[WORD_LENGTH];
	decimalToBinaryArray(WORD_LENGTH - 1, 1, binaryArray1);

	// Tow's Complemenlt: First invert the second binary, then add 1 to it
	invert(binaryArrayB, invertedBinaryB);
	add(invertedBinaryB, binaryArray1, negativeBinaryB); 
	
	add(binaryArrayA, negativeBinaryB, binaryArrayResult);	
}


void and(int binaryArrayA[], int binaryArrayB[], int *binaryArrayResult)
{
	int i;	

	for(i = WORD_LENGTH - 1; i >= 0; i--){
		binaryArrayResult[i] = binaryArrayA[i] & binaryArrayB[i]; 
	}
}


void or(int binaryArrayA[], int binaryArrayB[], int *binaryArrayResult)
{
	int i;	

	for(i = WORD_LENGTH - 1; i >= 0; i--){
		binaryArrayResult[i] = binaryArrayA[i] | binaryArrayB[i]; 
	}
}


void nor(int binaryArrayA[], int binaryArrayB[], int *binaryArrayResult)
{
	int orBinaryArrayResult[WORD_LENGTH];

	// First make OR, then invert the result 
	or(binaryArrayA, binaryArrayB, orBinaryArrayResult);
	invert(orBinaryArrayResult, binaryArrayResult);
}


void invert(int binaryArray[], int *binaryArrayResult)
{
	int i;	

	for(i = WORD_LENGTH - 1; i >= 0; i--){
		binaryArrayResult[i] = binaryArray[i] ^ 1; 
	}	
}


void xor(int binaryArrayA[], int binaryArrayB[], int *binaryArrayResult)
{
	int i;	
	
	for(i = WORD_LENGTH - 1; i >= 0; i--){
		binaryArrayResult[i] = binaryArrayA[i] ^ binaryArrayB[i]; 
	}
}


flags getStatusFlags()
{
	return statusFlags;
}


