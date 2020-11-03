#define WORD_LENGTH 32
#define WORD_OPTION_LENGTH 3


typedef struct {
     unsigned int zeroFlag : 1;
     unsigned int overflowFlag : 1;
     unsigned int carryFlag : 1;
}flags;


int halfAdder(int bitA, int bitB, int *carryOut);

int fullAdder(int bitA, int bitB, int carryIn, int *carryOut);

void add(int binaryArrayA[], int binaryArrayB[], int *result);

void sub(int binaryArrayA[], int binaryArrayB[], int *result);

void and(int binaryArrayA[], int binaryArrayB[], int *result);

void or(int binaryArrayA[], int binaryArrayB[], int *result);

void nor(int binaryArray[], int binaryArrayB[], int *result);

void xor(int binaryArrayA[], int binaryArrayB[], int *result);

void checkZeroResult(int binaryArray[]);

void slt(int binaryArrayA[], int binaryArrayB[], int *result);

void invert(int binaryArray[], int *result);

