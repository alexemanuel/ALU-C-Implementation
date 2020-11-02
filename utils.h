#define WORDLENGTH 32
#define WORDFLAGLENGTH 3


void getBinaryFromFile(FILE* file, char* binaryArrayArray, int wordlength);

int binaryToDecimal(char binaryArray[]);

void binaryToDecimalArray(char binaryArray[], int *binaryDecimalArray);

void printResult(int binaryArrayA[], int binaryArrayB[], int binaryArrayOutput[], char *operation, flags statusFlags);

void decimalToBinaryArray(int index, int num, int *binaryArray);

void printBinaryArray(int binaryArray[]);

flags getStatusFlags();
