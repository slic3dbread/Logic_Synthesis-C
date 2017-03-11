/*************************functions.c*****************************************
Student Name: Nicholas Bastian & Benjamin Mcconville
Date: October 19th                           Course Name: ENGG 3190
Assignment Number: 2
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void printPrimeTable(char prime[][4],int minterms[], int primeTable[][20],int primeCount,int minCount, FILE* resultFile){
	int i=0, j=0;
	char * primeImp=malloc(sizeof(char)*5);
	
	fprintf(resultFile, "\n     |");
	for(i=0;i<16;i++){ 
		if(minterms[i]==-1){
		}
		else if (minterms[i]==-2){
		}
		else	
			fprintf(resultFile, "%#2d ",minterms[i]);  
	}
	fprintf(resultFile, "\n");
	
	for (i=0; i<minCount*4;++i){  
		fprintf(resultFile, "-");    
	}
	fprintf(resultFile, "\n");    

	
	for(j=0;j<primeCount;j++){
		if(prime[j][0]=='a'){/*a represents a removed prime*/
		}
		else{
			strncpy(primeImp,prime[j],4); /* PRINT OUT THE PRIME IMPLICANT*/
			fprintf(resultFile, "%#4s | ",primeImp);
			i=0;
			for(i=0;i<minCount;i++){
				if(minterms[i]!=-2){
					if(primeTable[i][j]==1)
						fprintf(resultFile, "X  ");
					else
						fprintf(resultFile, "_  ");
				}
			}
			fprintf(resultFile, "\n");
		}
	}
	free(primeImp);
	return;
}

int numberOfOnes(int value) {
    int count;
    for (count = 0; value != 0; count++, value &= value-1);
    return count;
}


bool compare(int x, int y)
{
	float z;
	z=x-y;
	
	while(z>1)
		z=z/2;
	
	if (z==1)
		return true;
	else
		return false;
}

char * printPrime(char * primeImp, int inputVar)
{
	char * returnVar=malloc(sizeof(char)*8);
	char varImp[8]={' ',' ',' ',' ',' ',' ',' ',' '};
	char letter[4]={'A','B','C','D'};
	int j=0, c=0;
	
	strncpy(returnVar, varImp, 8);

	for(j=0;j<inputVar;j++){
		if(primeImp[j]=='0'){
			varImp[c]=letter[j];
			c++;
			varImp[c]='\'';
			c++;
		}
		else if(primeImp[j]=='1'){
			varImp[c]=letter[j];
			c++;
		}
	}
	
	strncpy(returnVar, varImp, c);
	
	return returnVar;
}


/* Function to convert decimal to binary.*/

/*http://www.programmingsimplified.com/c/source-code/c-program-convert-decimal-to-binary*/
char *decimal_to_binary(int n)
{
   int c, d, count;
   char *pointer;

   count = 0;
   pointer = (char*)malloc(4+1);

   if ( pointer == NULL )
      exit(EXIT_FAILURE);

   for ( c = 3 ; c >= 0 ; c-- )
   {
      d = n >> c;

      if ( d & 1 )
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';

      count++;
   }
   *(pointer+count) = '\0';

   return  pointer;
}
