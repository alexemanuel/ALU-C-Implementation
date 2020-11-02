#include <stdio.h>
#include <math.h>
#include "ALUFunctions.h"
#include "utils.h"


void printResult(int binaryArrayA[], int binaryArrayB[], int binaryOutput[], char *operation, flags statusFlags)
{	
	printf("===================================\n");

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
	printf("===================================\n");
}


void printBinaryArray(int binaryArray[])
{
	int i;

	for(i = 0; i < WORDLENGTH; i++){
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


void binaryToDecimalArray(char binaryString[], int *binaryDecimalArray)
{	
	int i;
	
	for(i = WORDLENGTH - 1; i >= 0; i--){
		binaryDecimalArray[i] = binaryString[i] == '1';
	}
}


int binaryToDecimal(char binaryArray[])
{
	int decimal = 0;
	int i;
	
	for(i = WORDFLAGLENGTH -1; i >= 0; i--){
		decimal += pow(2, WORDFLAGLENGTH - 1 - i) * (binaryArray[i] == '1');
	}
	return decimal;
}


void getBinaryFromFile(FILE *file, char *binaryArrayArray, int wordlength) 
{
	fgets(binaryArrayArray, wordlength + 1, file);
	fgetc(file); //Skip blank space
}




