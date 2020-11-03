#include <stdio.h>
#include <math.h>
#include "ALUFunctions.h"
#include "utils.h"


void printResult(int binaryArrayA[], int binaryArrayB[], int binaryOutput[], char *operation, flags statusFlags)
{	
	printf("==========================================================\n");

	printf("Binary A:  ");	
	printBinaryArray(binaryArrayA);

	printf("Binary B:  ");
	printBinaryArray(binaryArrayB);

	printf("Operation: %s\n", operation);
	printf("---------\n");

	printf("Output Binary: ");
	printBinaryArray(binaryOutput);

	printf("Flags:\n");
	printf("Zero Flag     %d\n", statusFlags.zeroFlag);
	printf("OverFlow Flag %d\n", statusFlags.overflowFlag);
	printf("Carry Flag    %d\n", statusFlags.carryFlag);
	printf("===========================================================\n");
}


void printBinaryArray(int binaryArray[])
{
	int i;

	for(i = 0; i < WORD_LENGTH; i++){
		printf("%d", binaryArray[i]);
	}
	printf("\n");
}


void decimalToBinaryArray(int index, int num, int *array)
{
    array[index] = num % 2;

    if(index > 0)
        decimalToBinaryArray(--index, num / 2, array);
}


void binaryStringToBinaryArray(char binaryString[], int *binaryArray)
{	
	int i;
	
	for(i = WORD_LENGTH - 1; i >= 0; i--){
		binaryArray[i] = binaryString[i] == '1';
	}
}


int binaryStringToDecimal(char binaryString[])
{
	int decimal = 0;
	int i;
	
	for(i = WORD_OPTION_LENGTH -1; i >= 0; i--){
		decimal += pow(2, WORD_OPTION_LENGTH - 1 - i) * (binaryString[i] == '1');
	}
	return decimal;
}


void getBinaryStringFromFile(FILE *ptrFile, char *binaryString, int wordLength)
{
	fgets(binaryString, wordLength + 1, ptrFile);
	fgetc(ptrFile); //Skip blank space
}




