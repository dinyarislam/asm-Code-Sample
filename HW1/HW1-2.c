//=================================================================
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

#include <stdio.h>
#include <stdlib.h>

/* 
 Student Name: Dinyar Islam
 Date: 8 September 2021

ECE 2035 Homework 1-2

This is the only file that should be modified for the C implementation
of Homework 1.

Do not include any additional libraries.

Assume 9 < x < 32,768.
This program determines whether the square of x can be computed by
1) taking all but the least significant digit of x, adding this "upper" number to the square of itself, and 
2) concatenating the result of step 1 to the 2-digit square of the least significant digit of x.

For example, if x = 54, your program should determine whether 54^2 == 3016. 
    1) 5^2+5 = 30
    2) concat 30 w/ 4^2 = 16 to get 3016.

FOR FULL CREDIT (on all assignments in this class), BE SURE TO TRY
MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

Test Case 1 = x: 54, SQ: 2916, A: 3016, Result: 0
Test Case 2 = x: 53, SQ: 2809, A: 309, Result: 0
Test Case 3 = x: 75, SQ: 5625, A: 5625, Result: 1
Test Case 4 = x: 2225, SQ: 4950625, A: 4950625, Result: 1
Test Case 5 = x: 31875, SQ: 1016015625, A: 1016015625, Result: 1
Test Case 6 = x: 31676, SQ: 1003368976, A: 1003305636, Result: 0
Test Case 7 = x: 9264, SQ: 85821696, A: 85840216, Result: 0
Test Case 8 = x: 9265, SQ: 85840225, A: 85840225, Result: 1
Test Case 9 = x: 11288, SQ: 127418944, A: 127351264, Result: 0
Test Case 10 = x: 11285, SQ: 127351225, A: 127351225, Result: 1
**************************************************************************
ALSO, FILL IN THE ANSWER TO THIS QUESTION:
Suppose SQ is x squared and A is the value computed by steps 1 and 2 above.
What is true of all integers x for which SQ == A, but is not true for
integers where SQ != A?

YOUR ANSWER:
All integers x for which SQ == A have a least significant digit of 5 i.e. their right 
most digit is 5 as seen above in the example test cases, which is not the case for all 
the integers where SQ != A. In fact none of the integers for which SQ != A, have a least
significant digit of 5.
**************************************************************************
*/

//DO NOT change the following declaration (you may change the initial value).
int x = 54;
int SQ;
int A;
int Result;

/*
For the grading scripts to run correctly, the above declarations
must be the first lines of code in this file (for this homework
assignment only).  Under penalty of grade point loss, do not change
these lines, except to replace the initial values while you are testing
your code.  

Also, do not include any additional libraries.
 */

int main() {

  // insert your code here
  //Calculating SQ by squaring x:
  SQ = x * x;

  /*
  Calculating A using div and mod operators based on the given rule
  (mod or '%' allows us to isolate the Least Significant digit of the integer 
  and div or '/' allows us to isolate all the other digits except for the 
  least significant one for our calculations. Multiplying by 100 assists us
  with the concatination process and also allows padding of zeros when required):
  */
  A = ((x / 10) * (x / 10) + (x / 10)) * 100 + (x % 10) * (x % 10);
  
  //Checking if SQ and A are equal and setting Result to 1 or 0 accordingly
  if (SQ == A) {
    Result = 1;
  } else {
    Result = 0;
  }

  // your program should use this print statement
  printf("x: %d, SQ: %d, A: %d, Result: %d\n", x, SQ, A, Result);

  return 0;
}

