/*************************lab2.c*****************************************
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
#include "functions.h"

int main(void)
{
    int inputVar;
	int minterms[16];
	int dontCare[16];
	char * primeImp=malloc(sizeof(char)*5);
    char * outFile=malloc(sizeof(char)*125);
	FILE * inFile;/*The input file*/
	FILE * resultFile;/*The output file*/
    char * checkString;
	char varType;

	/*variables for calculation*/
	int numInSet;
	int numbersInSet[16];
	int firstArray[8][9];
	int secondArray[8][16][4];
	int thirdArray[20][20][4];
	int fourthArray[8][8];
	int z=0,i=0,j=0,k=0,increment=0,inc=0,primeCount=0,numCount=0,checkCount=0,onesValue=0; /*counting integers*/
	int varCount[5]={0,0,0,0,0};
	int setCount[5]={0,0,0,0,0};
	int count[3]={0,0,0};
	int check[16];
	int numbers[100];
	int primeSet[16][2];
	int checkSet[16];
	int checkSet2[16];
	int primeArray[16][8];

	/*Binary conversion*/
	char *tempS;
	char temp1[4];
	char prime[10][4];

	/*Essential prime variables*/
	int primeTable[20][20];
	int minCount=0;
	int primeRemoved=0;
	int reductionCount=0;
	int b=0,p=0,y=0,x=0;
	char essential[15][4];
	int essentialCount[8];
	int greaterRow=0;
    int lesserRow=0;
    int equalTo=0;
    int c=0,a=0,m=0;
    int greaterColumn = 0;
    int lesserColumn = 0;

	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			for(k=0;k<4;k++){
				thirdArray[i][j][k]=-1;
				primeTable[i][j]=0; /*sets the default of the table to 0*/
			}
		}
	}
	i=0;
	j=0;
	k=0;
    inFile=fopen("input.txt", "r");/*opens input file*/
	resultFile=fopen("output.txt", "w");/*opens output file*/
    fgets(outFile,125,inFile);/*checks the first line*/

    while(!feof(inFile))
    {   /*Tokenizes base on a period, space and the EOF*/
        checkString=strtok(outFile, ". \n\t");
        varType=checkString[0];
		if (varType=='i'){	/*Takes the tokenized line and converts to an integer*/
			inputVar=atoi(strtok(NULL, ". \n\t"));
		}
		/*get minterms form text*/
		else if (varType=='m'){	/*Sets the default numbers in the set to -1*/
			j=0;
			for(j=0;j<16;j++){
				minterms[j]=-1;
			}
			i=0;
			fgets(outFile,125,inFile);
			checkString=strtok(outFile, ". \n\t");
			if(checkString!=NULL){
				sscanf(checkString, "%d", &minterms[i]);
				i++;
			}
			checkString=strtok(NULL, ". \n\t");
			while(checkString!=NULL){
				sscanf(checkString, "%d", &minterms[i]);
				i++;
				if(i>15){
					i=14;
				}
				checkString=strtok(NULL, ". \n\t");
			}
		}
		/*get dontCares form text*/
		else if (varType=='d'){	/*Sets the default numbers in the set to -1*/
			j=0;
			for(j=0;j<16;j++){
				dontCare[j]=-1;
			}
			i=0;
			fgets(outFile,125,inFile);
			checkString=strtok(outFile, ". \n\t");
			if(checkString!=NULL){
				sscanf(checkString, "%d", &dontCare[i]);
				i++;
			}
			checkString=strtok(NULL, ". \n\t");
			while(checkString!=NULL){
				sscanf(checkString, "%d", &dontCare[i]);
				i++;
				if(i>15){
					i=14;
				}
				checkString=strtok(NULL, ". \n\t");
			}
		}
		else{
			printf("There was an error reading the file!\n");
		}
		fgets(outFile,125,inFile);
	}

	/*Calculation*/
	numInSet=0;
	i=0;
	/*Sets the default numbers in the set to -1*/
	j=0;
	for(j=0;j<16;j++){
		numbersInSet[j]=-1;
	}

	/*Writing to output file*/
	fprintf(resultFile, ".i %d\t /* the function f has %d input variables: A, B, C, D */\n", inputVar, inputVar);
	fprintf(resultFile, ".m   \t /* On Set */\n");

	/*puts the minterm array in the numbersInSet array*/
	while(minterms[i]!=-1){
		fprintf(resultFile, "%d ",minterms[i]); /*Writes the minterms to the output file*/
		numbersInSet[numInSet]=minterms[i];
		i++;
		numInSet++;
	}
	/*Title for the Don't cares*/
	fprintf(resultFile, "\n.d   \t /* Don't Care Set DC-SET */\n");

	/*appends dontCare array in the numbersInSet array*/
	i=0;
	while(dontCare[i]!=-1){
		fprintf(resultFile, "%d ",dontCare[i]); /*Writes the Dontcares to the output file*/
		numbersInSet[numInSet]=dontCare[i];
		i++;
		numInSet++;
		if (numInSet>15){
			numInSet=15;
		}
	}

	/*sets the primeArray and check array to -1 so when a variable is added we can check when it ends*/
	for(i=0;i<16;i++){
		for(j=0;j<8;j++){
			primeArray[i][j]=-1;
		}
		check[i]=-1;
	}
	/*sets the zero to negative 1 by default untill its found*/
	firstArray[0][0]=-1;
	/*Sorts all of the numbers in the set by binary 1's*/
	for(j=0; j<numInSet; j++){
		if(numbersInSet[j] != -1){
			onesValue = numberOfOnes(numbersInSet[j]);
			if (onesValue == 1){
				firstArray[1][varCount[1]] = numbersInSet[j];
				varCount[1]++;
			}
			else if (onesValue == 2){
				firstArray[2][varCount[2]] = numbersInSet[j];
				varCount[2]++;
			}
			else if (onesValue == 3){
				firstArray[3][varCount[3]] = numbersInSet[j];
				varCount[3]++;
			}
			else if (onesValue == 4){
				firstArray[4][varCount[4]] = numbersInSet[j];
				varCount[4]++;
			}
			else{
				firstArray[0][varCount[0]] = 0;
				varCount[0]++;
			}
		}
	}
	/*Compares and stores minterms that are not in the the next column*/
	z=0;
	i=0;
	j=0;
	k=0;
	for(z=0;z<inputVar;z++){
		for(i=0;i<varCount[z];i++){
			for(j=0;j<varCount[z+1];j++){
				if(compare(firstArray[z+1][j], firstArray[z][i])){
					secondArray[z][setCount[z]][0]=firstArray[z][i];
					secondArray[z][setCount[z]][1]=firstArray[z+1][j];
					/*checks if the variable is used*/
					numbers[k]=firstArray[z][i];
					numbers[k+1]=firstArray[z+1][j];
					k=k+2;
					setCount[z]++;
				}
			}
		}
	}
	i=0;
	j=0;
	/*compares the numbers used in the second column to the original set of numbers*/
	for(i=0;i<numInSet;i++){
		for(j=0;j<k;j++){
			if(numbersInSet[i]==numbers[j]){
				check[i]=1;
			}
		}
	}
	checkCount=0;
	i=0;
	/*Numbers that aren't in the numberSet are prime implicants and the numbers that are get passed on to the next checking section*/
	for(i=0;i<numInSet;i++){
		if(check[i]==-1){
			primeArray[primeCount][0]=numbersInSet[i];
			primeCount++;
		}
		else{
			checkSet[checkCount]=numbersInSet[i];
			checkCount++;
		}
	}
	/*Third colum*/
	z=0;
	j=0;
	k=0;
	i=0;
	for(z=0;z<inputVar-1;z++){
		for(j=0;j<setCount[z];j++){
			for(k=0;k<setCount[z+1];k++){
				if(((secondArray[z][j][1]-secondArray[z][j][0])==
				(secondArray[z+1][k][1]-secondArray[z+1][k][0]))&&(secondArray[z+1][k][0]>secondArray[z][j][1])&&
				compare(secondArray[z+1][k][1],secondArray[z][j][1])){
					thirdArray[z][count[z]][0]=secondArray[z][j][0];
					if(secondArray[z+1][k][0]<secondArray[z][j][1]){
						thirdArray[z][count[z]][1]=secondArray[z+1][k][0];
						thirdArray[z][count[z]][2]=secondArray[z][j][1];
					}
					else{
						thirdArray[z][count[z]][1]=secondArray[z][j][1];
						thirdArray[z][count[z]][2]=secondArray[z+1][k][0];
					}
					thirdArray[z][count[z]][3]=secondArray[z+1][k][1];

					count[z]++;
					/*stores the numbers used in an array*/
					numbers[i]=secondArray[z][j][0];
					numbers[i+1]=secondArray[z+1][k][0];
					numbers[i+2]=secondArray[z][j][1];
					numbers[i+3]=secondArray[z+1][k][1];
					i=i+4;
				}
			}
		}
	}
	/*Check which numbers were not used in the second column*/
	k=0;
	/*Resets the array*/
	for(k=0;k<16;k++){
		check[k]=-1;
	}
	k=0;
	j=0;
	z=0;
	for(k=0;k<checkCount;k++){
		for(j=0;j<i;j++){
			if(checkSet[k]==numbers[j]){
				check[k]=1;
			}
		}
	}
	checkCount=0;
	i=0;
	/*Numbers that aren't in the numberSet are checked in the next function and the numbers that are get passed on to the next checking section*/
	for(i=0;i<k;i++){
		if(check[i]==-1){
			numbers[numCount]=checkSet[i];
			numCount++;
		}
		else{
			checkSet2[checkCount]=checkSet[i];
			checkCount++;
		}
	}
	z=0;
	i=0;
	k=0;
	/*stores the location of the secondArray colum set's that are prime implicats*/
	for(z=0;z<inputVar-1;z++){
		for(i=0;i<setCount[z];i++){
			for(k=0;k<numCount;k++){
				if(secondArray[z][i][0]==numbers[k]||secondArray[z][i][1]==numbers[k]){
					primeSet[increment][1]=z;
					primeSet[increment][0]=i;
					inc=1;
				}
			}
			if(inc==1){
				increment++;
			}
			inc=0;
		}
	}
	i=0;
	j=0;
	/*puts the prime Implicants in it's array*/
	for(i=0;i<increment;i++){
		primeArray[primeCount][0]=secondArray[primeSet[i][1]][primeSet[i][0]][0];
		primeArray[primeCount][1]=secondArray[primeSet[i][1]][primeSet[i][0]][1];

		primeCount++;
	}
	/*fourth colum*/
	z=0;
	i=0;
	j=0;
	k=0;
	increment=0;
	for(z=0;z<inputVar-2;z++){
		for(i=0;i<count[z];i++){
			for(j=0;j<count[z+1];j++){
				if(((thirdArray[z][i][3]-thirdArray[z][i][2])==
				(thirdArray[z][i][2]-thirdArray[z][i][1]))&&((thirdArray[z+1][j][3]-thirdArray[z+1][j][2])==
				(thirdArray[z+1][j][2]-thirdArray[z+1][j][1]))&&((thirdArray[z][i][3]-thirdArray[z][i][2])==
				(thirdArray[z+1][j][2]-thirdArray[z+1][j][1]))){
					if((fourthArray[increment-1][0]==thirdArray[z][i][0])&&
					(fourthArray[increment-1][7]==thirdArray[z+1][j][3])){
					}
					else{
						fourthArray[increment][0]=thirdArray[z][i][0];
						/*sorts based on relationship of the previous set to order from smallest to greatest*/
						if(thirdArray[z][i][3]<thirdArray[z+1][j][0]){
							fourthArray[increment][1]=thirdArray[z][i][1];
							fourthArray[increment][2]=thirdArray[z][i][2];
							fourthArray[increment][3]=thirdArray[z][i][3];
							fourthArray[increment][4]=thirdArray[z+1][j][0];
							fourthArray[increment][5]=thirdArray[z+1][j][1];
							fourthArray[increment][6]=thirdArray[z+1][j][2];
						}
						else{
							fourthArray[increment][1]=thirdArray[z+1][j][0];
							fourthArray[increment][2]=thirdArray[z][i][1];
							fourthArray[increment][3]=thirdArray[z+1][j][1];
							fourthArray[increment][4]=thirdArray[z][i][2];
							fourthArray[increment][5]=thirdArray[z+1][j][2];
							fourthArray[increment][6]=thirdArray[z][i][3];
						}
						fourthArray[increment][7]=thirdArray[z+1][j][3];

						/*Puts the set into the primeArray and incrments the count by 1*/
						primeArray[primeCount][0]=fourthArray[increment][0];
						primeArray[primeCount][1]=fourthArray[increment][1];
						primeArray[primeCount][2]=fourthArray[increment][2];
						primeArray[primeCount][3]=fourthArray[increment][3];
						primeArray[primeCount][4]=fourthArray[increment][4];
						primeArray[primeCount][5]=fourthArray[increment][5];
						primeArray[primeCount][6]=fourthArray[increment][6];
						primeArray[primeCount][7]=fourthArray[increment][7];
						primeCount++;

						/*A set of numbers used in the fouth level set*/
						numbers[k]=fourthArray[increment][0];
						numbers[k+1]=fourthArray[increment][1];
						numbers[k+2]=fourthArray[increment][2];
						numbers[k+3]=fourthArray[increment][3];
						numbers[k+4]=fourthArray[increment][4];
						numbers[k+5]=fourthArray[increment][5];
						numbers[k+6]=fourthArray[increment][6];
						numbers[k+7]=fourthArray[increment][7];
						k=k+8;

						increment++;
					}
				}
			}
		}
	}
	/*Check which numbers were not used in the third column*/
	i=0;
	/*Resets check*/
	for(i=0;i<16;i++){
		check[i]=-1;
	}
	i=0;
	j=0;
	z=0;
	/*checks previously passed check to numbers passed when there is a fourth level clolumn*/
	for(i=0;i<checkCount;i++){
		for(j=0;j<k;j++){
			if(checkSet2[i]==numbers[j]){
				check[i]=1;
			}
		}
	}
	checkCount=0;
	i=0;
	numCount=0;
	for(i=0;i<k;i++){
		if(check[i]==-1){
			numbers[numCount]=checkSet2[i];
			numCount++;
		}
	}
	z=0;
	i=0;
	k=0;
	j=0;
	/*finds the location of the prime Implicants*/
	for(z=0;z<inputVar-1;z++){
		for(i=0;i<setCount[z];i++){
			for(k=0;k<numCount;k++){
				if(thirdArray[z][j][0]==numbers[k]||thirdArray[z][j][1]==numbers[k]
				||thirdArray[z][j][2]==numbers[k]||thirdArray[z][j][3]==numbers[k]){
					primeSet[j][1]=z;
					primeSet[j][0]=i;
					inc=1;
				}
			}
			if(inc==1){
				j++;
			}
			inc=0;
		}
	}
	i=0;
	/*Puts the prime Implicants in the array*/
	for(i=0;i<j;i++){
		primeArray[primeCount][0]=thirdArray[primeSet[i][1]][primeSet[i][0]][0];
		primeArray[primeCount][1]=thirdArray[primeSet[i][2]][primeSet[i][0]][1];
		primeArray[primeCount][3]=thirdArray[primeSet[i][3]][primeSet[i][0]][2];
		primeArray[primeCount][4]=thirdArray[primeSet[i][4]][primeSet[i][0]][3];

		primeCount++;
	}
	i=0;
	k=0;
	if(increment==0){
		for(i=0;i<8;i++){
			for(k=0;k<20;k++){
				if(thirdArray[i][k][0]!=-1){
					primeArray[primeCount][0]=thirdArray[i][k][0];
					primeArray[primeCount][1]=thirdArray[i][k][1];
					primeArray[primeCount][2]=thirdArray[i][k][2];
					primeArray[primeCount][3]=thirdArray[i][k][3];

					primeCount++;
				}
			}
		}
	}

	/*Converts from prime implicants to 0's,1's and -'s*/
	j=0;
	i=0;
	/*changes the prime implicants from integers to 0's and dashes, then stores in a double array of characters*/
	for(j=0; j<primeCount; j++){
        for(i=0; i<8; i++){
            if(primeArray[j][i]!= -1){
                tempS = decimal_to_binary(primeArray[j][i]); /*converts the number to binary and moves to a temp int*/
                strcpy(temp1, tempS);
                free(tempS);
                if(i==0){
                    k=0;
                    for(k=0; k<4; k++)
                        prime[j][k] = temp1[k];}
                if(i>0){
                    k=0;
                    for(k=0; k<4; k++){
                        if(prime[j][k] != temp1[k] && prime[j][k]!= '-')/*checks to make sure there isn't already a dash, and that they arent already equal*/{
                            prime[j][k] = '-'; /*adds a dash when there is a one and a zero*/
                        }
                    }
                }
            }
        }
    }


	/*Writes the Prime Implicants to the output file*/
	fprintf(resultFile, "\n.p %d \t /* There are %d Prime Implicants*/\n", primeCount, primeCount);
	i=0;
	for(i=0;i<primeCount;i++){
		strncpy(primeImp,prime[i],4); /* PRINT OUT THE PRIME IMPLICANT*/
		fprintf(resultFile, "%s    \t /* %s */\n",primeImp, printPrime(primeImp,inputVar));
	}



	/*Creates the table of minterms and prime Implicants*/
	i=0;
	j=0;
	k=0;

	while(minterms[i]!=-1||i==15){
		for(j=0;j<primeCount;j++){
			while(primeArray[j][k]!= -1){
				if(primeArray[j][k]==minterms[i])
					primeTable[i][j]=1; /*Writes 1 if the minterm is in the prime implicant*/
				k++;
			}
			k=0;
		}
		i++;
	}
	minCount=i;

	/*Writes the Prime Implicant table*/
	fprintf(resultFile, "\nThe Initial prime Table:\n");
	printPrimeTable(prime,minterms,primeTable,primeCount,minCount,resultFile);
	
	x=0;
	y=0;
	p=0;
	b=0;
	k=0;
	i=0;
	
	for(x=0; x<16; x++){ /*minterm loops*/
		reductionCount = 0;
		for(y=0; y<10; y++){ /*primimplicant search for each minterm*/
			if(primeTable[x][y] != 0){ /*checks to see if the prime implicant exists in each minterm*/
				reductionCount = reductionCount+1;
				k=y;
			}

		}
		if(reductionCount==1){
			for(p=0; p<4; p++){
				essential[k][p] = prime[k][p];/*if an essential prime implicant exists, it is put into an essential array*/
			}
			prime[k][0] = 'a';
			essentialCount[b]=k;

			for(i=0; i<16; i++){ /*minterm loops*/
				for(j=0;j<8;j++){
					if(primeArray[k][j]==minterms[i]&&minterms[i]!=-1&&minterms[i]!=-2&&primeArray[k][j]!=-1)
						minterms[i]=-2;
				}
			}
			b++;
			primeRemoved++;
			
		}
	}
	
	fprintf(resultFile, "\nThe prime Table after removing essential prime implicants:\n");
	printPrimeTable(prime,minterms,primeTable,primeCount,minCount,resultFile);

	for(m=0;m<16;m++){
	
		y=0;
		k=0;
		x=0;
		/*This loop will clear out minterms with no minterms in the table*/
		for(y=0; y<10; y++){ /*primimplicant search for each minterm*/
			reductionCount = 0;
			for(x=0; x<16; x++){ /*primimplicant search for each minterm*/
				if(primeTable[x][y] != 0&&minterms[x]!=-1&&minterms[x]!=-2){ /*checks to see if the prime implicant exists in each minterm*/
					reductionCount++;
				}
			}
			if(reductionCount==0){
				prime[y][0] = 'a';
			}
		}
		
		/*Row reduction*/
		x=0;
		y=0;
		c=1;
		z=0;
		for(y=0; y<primeCount; y++){ /*primimplicant search for each minterm*/
			a=0;
			for(z=0+c; z<primeCount; z++){ /*The second row being compared, subtracted by one for each loops through*/
				greaterRow = 0; /*reset the counters before a new minterm is compared*/
				lesserRow = 0;
				equalTo = 0;
				for(x=0; x<16; x++){ /*minterm loops*/
					if(z!=y && minterms[x]!=-2 && minterms[x]!=-1 && a!=1&&prime[z][0]!='a'){/*To make sure that we loop through all of the primes without checking the same two twice*/
						if(primeTable[x][y] == primeTable[x][z]){ /*checks to see if the prime implicant is greater then the other rows*/
							equalTo = equalTo+1;
						}
						if(primeTable[x][y] > primeTable[x][z]){
							 /*checks to see if the prime implicant is greater then the other rows*/
							greaterRow = greaterRow+1;
						}
						if(primeTable[x][y] < primeTable[x][z]){/*checks to see if the prime implicant is greater then the other rows*/
							lesserRow = lesserRow+1;
						}
					}
				}
				if(greaterRow>0 && lesserRow==0){/*Checks to see if row 1 is greater then row 2, if so removes row 1*/
					/*remove row 2*/
					prime[z][0] = 'a';
				}
				else if(lesserRow>0 && greaterRow==0){/*Checks to see if row 2 is greater the row 1, if so removes row 2*/
					/*remove row 1*/
					prime[y][0] = 'a';
					a=1;
				}
				else if(lesserRow==0 && greaterRow==0 && equalTo>0){/*Checks to see if row 1 is equal to row 2, if so removes row 1*/
					/*remove row 1*/
					prime[y][0] = 'a';
					a=1;
				}
			}
			c++;
		}

		/*Column reduction*/

		x=0;
		y=0;
		c=1;
		z=0;
		for(y=0; y<minCount; y++) /*minterm search for each column*/
		{
			a=0;
			for(z=0+c; z<minCount; z++) /*The second row being compared, subtracted by one for each loops through*/
			{
				greaterColumn = 0; /*reset the counters before a new minterm is compared*/
				lesserColumn = 0;
				equalTo = 0;
				for(x=0; x<primeCount; x++) /*minterm loops*/
				{
					if(z!=y && minterms[y]!=-2 && minterms[y]!=-1 && a!=1 && minterms[z]!=-2 && minterms[z]!=-1 &&prime[x][0]!='a')/*To make sure that we loop through all of the primes without checking the same two twice*/
					{
						/*printf("%d\n",primeTable[x][y]);*/
						if(primeTable[y][x] == primeTable[z][x]) /*checks to see if the prime implicant is greater then the other rows*/
						{
							equalTo = equalTo+1;
						}

						if(primeTable[y][x] < primeTable[z][x]) /*checks to see if the prime implicant is greater then the other rows*/
						{
							lesserColumn = lesserColumn+1;
						}

						if(primeTable[y][x] > primeTable[z][x]) /*checks to see if the prime implicant is greater then the other rows*/
						{
							greaterColumn = greaterColumn+1;
						}
					}
				}

				if(greaterColumn>0 && lesserColumn==0){
					/*remove row 1*/
					minterms[y]=-2;
					a=1;
				}
				else if(lesserColumn>0 && greaterColumn==0){
					/*remove row 2*/
					minterms[z]=-2;
				}
				else if(lesserColumn==0 && greaterColumn==0 && equalTo>0){
					/*remove row 1*/
					minterms[y]=-2;
					a=1;
				}
			}
			c++;
		}
    }
	
	
	/*Writes the Prime Implicant table*/
	fprintf(resultFile, "\nThe fully reduced prime implicant table:\n");
	printPrimeTable(prime,minterms,primeTable,primeCount,minCount,resultFile);
	
	
	fprintf(resultFile, "\nThe function is:\nF =");
	
	i=0;
	x=0;
	/*Prints the essential prime implicants*/
	for(i=0;i<b;i++){
		x=essentialCount[i];
		strncpy(primeImp,essential[x],4);
		fprintf(resultFile, "%s ",printPrime(primeImp,inputVar));
		if(i<(b-1))
			fprintf(resultFile, "+ ");
	}
	
	i=0;
	k=0;
	/*Prints the remaining prime implicants*/
	for(i=0;i<primeCount;i++){
		if(b==0&&k==0&&prime[i][0]!='a'){
			k++;
		}
		else if(prime[i][0]!='a'){
			fprintf(resultFile, "+ ");
		}
			
		if(prime[i][0]!='a'){
			strncpy(primeImp,prime[i],4); /* PRINT OUT THE PRIME IMPLICANT*/
			fprintf(resultFile, "%s",printPrime(primeImp,inputVar));
		}
	}

	fprintf(resultFile, "\n.end\n");
	free(primeImp);
	free(outFile);
    fclose(inFile);
	fclose(resultFile);
    return 0;
}
