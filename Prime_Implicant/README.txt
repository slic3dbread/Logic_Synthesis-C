###############################################################################
###############################################################################
###########     Name: Benjamin McConville, Nicholas Bastian         ###########
###########     Date 09-05-2015    File:lab2   Course:ENGG3190      ###########
###############################################################################
###############################################################################
###############################################################################

How to run:
	-type make while inside the folder ENGG3190
	-then type ./run to execute the program on linux
	-then type ./run.exe to execute the program on windows cygwin

##########################################################################################
Files included:
	lab2.c		input.txt		ouput.txt		README.txt		
	makefile	functions.c		functions.h

##########################################################################################
lab2.c
-Gets the variable size, minterm set, and don't care set
-Calculates the prime implicants then ouputs them to the output.txt file
-Then outputs the prime Implicant table and the reduced function


##########################################################################################
input.txt 
sample file:
.i 4
.m
4 5 6 8 9 10 13 11
.d
0 7 12 14 15

Notes:
-the .i, .m, and .d must be in this order and spaces must be used as delimiters
-the input file does not check for duplicates of in the set's 


##########################################################################################
output.txt
Sample file:
.i 4	 /* the function f has 4 input variables: A, B, C, D */
.m   	 /* On Set */
4 5 6 8 9 10 13 
.d   	 /* Don't Care Set DC-SET */
0 7 15 
.p 7 	 /* There are 7 Prime Implicants*/
0-00    	 /* A'C'D' */
-000    	 /* B'C'D' */
100-    	 /* AB'C' */
10-0    	 /* AB'D' */
1-01    	 /* AC'D */
01--    	 /* A'B */
-1-1    	 /* BD */

     | 4  5  6  8  9 10 13 
----------------------------
0-00 | X  _  _  _  _  _  _  
-000 | _  _  _  X  _  _  _  
100- | _  _  _  X  X  _  _  
10-0 | _  _  _  X  _  X  _  
1-01 | _  _  _  _  X  _  X  
01-- | X  X  X  _  _  _  _  
-1-1 | _  X  _  _  _  _  X  

     | 8  9 10 13 
----------------------------
0-00 | _  _  _  _  
-000 | X  _  _  _  
100- | X  X  _  _  
10-0 | X  _  X  _  
1-01 | _  X  _  X  
-1-1 | _  _  _  X  

     | 9 13 
----------------------------
0-00 | _  _  
-000 | _  _  
100- | X  _  
1-01 | X  X  
-1-1 | _  X  

     | 9 13 
---------------------------- 
100- | X  _  
1-01 | X  X  
-1-1 | _  X  

     | 9 13 
----------------------------  
1-01 | X  X  

The function is:
F = A'B + AB'D' + AC'D
	
	
##########################################################################################
Constraints:
-the .i, .m, and .d must be in this order and spaces must be used as delimiters
-the input file does not check for duplicates of in the set's 
-i must be set to 4


##########################################################################################

Citations:
char *decimal_to_binary(int n)
/*http://www.programmingsimplified.com/c/source-code/c-program-convert-decimal-to-binary*/