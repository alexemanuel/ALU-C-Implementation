#define WORD_LENGTH 32
#define WORD_OPTION_LENGTH 3


void getBinaryStringFromFile(FILE *ptrFile, char *binaryString, int wordLength);

int binaryStringToDecimal(char binaryArray[]);

void binaryStringToBinaryArray(char binaryString[], int *binaryArray);

void printResult(int binaryArrayA[], int binaryArrayB[], int binaryArrayOutput[], char *operation, flags statusFlags);

void decimalToBinaryArray(int index, int num, int *binaryArray);

void printBinaryArray(int binaryArray[]);

flags getStatusFlags();
