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
 Date: 1 October 2021

ECE 2035 Project 1-1

This is the only file that should be modified for the C implementation
of Project 1.

Do not include any additional libraries.
------------------------------------------

This program locates a part of a specified color in a pile of parts and reports
its bounding box (Upper left corner pixel, Lower right corner pixel) and 
the part's color code. The pixels are specified as linear offsets from the 
pile image base.*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

int main(int argc, char *argv[]) {
   int	             PileInts[1024];
   // This allows you to access the pixels (individual bytes)
   // as byte array accesses (e.g., Pile[25] gives pixel 25):
   char *Pile = (char *)PileInts;

   int	             NumInts, ColorToFind=0;
   int               UpperLeft=0, LowerRight=0;
   int  Load_Mem(char *, int *);

   if (argc != 3) {
     printf("usage: ./P1-1 testcase_file color_code\n");
     exit(1);
   }
   ColorToFind = atoi(argv[2]);
   NumInts = Load_Mem(argv[1], PileInts);
   if (NumInts != 1024) {
      printf("valuefiles must contain 1024 entries\n");
      exit(1);
   }

   if (DEBUG){
     printf("Pile[0] is Pixel 0: 0x%02x\n", Pile[0]);
     printf("Pile[107] is Pixel 107: 0x%02x\n", Pile[77]);
   }

   /* Your program goes here */
   int ULRow = 63;  //The upper-left pixel's row
   int ULCol = 63;  //The upper-left pixel's column
   int LRRow = 38;   //The lower-right pixel's row
   int LRCol = 0;   //The lower-right pixel's column
   int row; //row index
   int col; //column index
   //int flag1 = 0;
   int pixel;
   //int flag2 = 0;

   //Indexing through the array using a row-column concept and 
   //identifying and storing the row and column indices of the 
   //two pixels in the upper-left and lower-right corners of the
   //bounding box
   for (row = 1; row < ULRow; row++) {
      for (col = 1; col < 63; col++) {
         if ((int) (Pile[row * 64 + col]) == ColorToFind) {
            ULRow = row;
            //ULCol = col;
            if (ULRow == row) {
               pixel = row * 64 + col + 64;
               LRRow = ULRow;
               while ((int) (Pile[pixel]) == ColorToFind || (int) Pile[pixel + 64] == ColorToFind) {
                  LRRow++;
                  pixel = pixel + 64;
                  col = 63;
               }
            }
         }
      }
   }

   for (col = 1; col < ULCol; col++) {
      for (row = ULRow; row < LRRow; row++) {
         if ((int) (Pile[row * 64 + col]) == ColorToFind) {
            ULCol = col;
            if (ULCol == col) {
               pixel = row * 64 + col + 1;
               LRCol = ULCol;
               while ((int) (Pile[pixel]) == ColorToFind || (int) Pile[pixel + 1] == ColorToFind) {
                  LRCol++;
                  pixel = pixel + 1;
                  row = 63;
               }
            }
         }
      }
   }
   //printf("%d, %d", LRRow, LRCol);

   //Calculating the pixels numbers using the ULRow, ULCol, LRRow, and LRCol values
   UpperLeft = ULRow * 64 + ULCol;
   LowerRight = LRRow * 64 + LRCol;
   printf("The part is located at: %d, %d, color: %d\n",
	  UpperLeft, LowerRight, ColorToFind);
   exit(0);
}

/* This routine loads in up to 1024 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < 1024; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
         if (NumVals == 2)
            IntArray[N] = Value;
         else
            break;
      }
      fclose(FP);
      return N;
   }
}
