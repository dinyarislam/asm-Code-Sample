//=================================================================
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

/*    
Please fill in the following
 Student Name: Dinyar Islam
 Date: 17 September 2021

ECE 2035 Homework 2-1

This is the only file that should be modified for the C implementation
of Homework 2.

Do not include any additional libraries.
-----------------------------------------------

   When Harry Met Sally

This program finds the total number of years in which Harry and Sally
live in the same city at the same time.
*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

/* City IDs used in timelines. */
enum Cities{ London, Boston, Paris, Atlanta, Miami, 
             Tokyo, Metz, Seoul, Toronto, Austin };

int main(int argc, char *argv[]) {
   int	HarryTimeline[10];
   int	SallyTimeline[10];
   int	NumNums, SumYears=0;
   int  Load_Mem(char *, int *, int *);
   void Print_Timelines(int *, int *);

   /* You may add more local variables here if needed. */
   if (argc != 2) {
     printf("usage: ./HW2-1 valuefile\n");
     exit(1);
   }
   NumNums = Load_Mem(argv[1], HarryTimeline, SallyTimeline);
   if (NumNums != 20) {
     printf("valuefiles must contain 20 entries\n");
     exit(1);
   }

   /* Your program goes here. */
   int i = 0; // index counter for HarryTimeline 
   int j = 0; // index counter for SallyTimeline 
   int index1 = 0; //index1 is for tracking the number of years Harry spent in each city
   int index2 = 0; //index2 is for tracking the number of years Sally spent in each city

    while (i < 10 && j < 10) {
      if (index1 >= HarryTimeline[i]) {
        i=i+2;       //increments the city code for Harry
        index1 = 0;  //resets the number of years counter for Harry
      }
      if (index2 >= SallyTimeline[j]) {
        j = j+2;     //increments the city code for sally
        index2 = 0;  //resets the number of years counter for Sally
      }
      if ((i + 1 < 10 && j + 1 < 10) && (HarryTimeline[i + 1] == SallyTimeline[j + 1])) {  //increments SumYears when they were
        SumYears++;                                        //in the same city
      }
      index1++;       //increments the city counters for each city
      index2++;
    }

   /* Use a statement like this to print information helpful to
      debugging (e.g., the current value of some variable).
      Set DEBUG to 1 using the #define above when debugging, but
      reset it back to 0 before submitting your code so that your
      program doesn't confuse the autograder with superfluous prints. */
   if (DEBUG){
     Print_Timelines(HarryTimeline, SallyTimeline);
     printf("Sample debugging print statement. argc: %d \n", argc);
   }

   // your program should use this print statement
   printf("Total number of years in which both lived in the same city: %d\n", SumYears);
   return 0;
}

/* This subroutine loads in up to 20 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray1[], int IntArray2[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
     printf("%s could not be opened; check the filename\n", InputFileName);
     return 0;
   } else {
     for (N=0; N < 20; N++) {
       NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
       if (NumVals == 2)
	 if (N < 10)
	   IntArray1[N] = Value;
	 else
	   IntArray2[N-10] = Value;
       else
	 break;
     }
     fclose(FP);
     return N;
   }
}

/* Colors used to display timelines.
https://en.wikipedia.org/wiki/ANSI_escape_code#Colors */

const char *colors[10] = {"\x1b[30;41m", // red
			  "\x1b[30;42m", // green
			  "\x1b[30;43m", // yellow
			  "\x1b[30;44m", // blue
			  "\x1b[30;45m", // magenta
			  "\x1b[30;46m", // cyan (light blue)
			  "\x1b[30;47m", // white bkgd
			  "\x1b[30;103m", // bright yellow
			  "\x1b[30;104m", // bright blue
			  "\x1b[30;106m"}; // bright cyan

#define RESET      "\x1b[0m"

void Print_Years(){
  int i;
  printf("  ");
  for (i=90; i<120; i++){
    printf("%3d", i%100);
  }
  printf("\n");
}

void Print_Timeline(int Timeline[]){
  int j, duration, city;
  int scale = 3;
  char interval[6];
  for (j=0; j<10; j=j+2){
    duration = Timeline[j];
    city     = Timeline[j+1];
    snprintf(interval, sizeof(interval), "%%%dd", duration*scale);
    printf("%s", colors[city]); // start highlighting in city's color
    printf(interval, city);
  }
  printf(RESET); // stop highlighting
  printf("\n");
}


void Print_Timelines(int HarryTimeline[], int SallyTimeline[]) {
  Print_Years();
  printf("H: ");

  Print_Timeline(HarryTimeline);

  printf("S: ");
  Print_Timeline(SallyTimeline);
}
