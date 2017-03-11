/*This function is used to convert a string of 1's 0's and -'s into a ABCD set with ' if neccesary*/
char * printPrime(char * primeImp, int inputVar);
/*subtracts y from x and returns true if the difference is a power of 2*/
bool compare(int x, int y);
/*Finds the number of binary 1's in an integer*/
int numberOfOnes(int value);
/*converts an integer into binary*/
char *decimal_to_binary(int n);
/*Prints out the prime Table in the output file*/
void printPrimeTable(char prime[][4],int minterms[],int primeTable[][20],int primeCount,int minCount, FILE* resultFile);
