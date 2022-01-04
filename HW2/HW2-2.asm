#=================================================================
# Copyright 2021 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================

#     When Harry Met Sally
#
# HW2-2
# Student Name: Dinyar Islam
# Date: 17 September 2021
#
# This program finds the total number of years during which Harry and Sally
# lived in the same city at the same time.
#
#  required output register usage:
#  $2: total number of years in same city at same time
#  result must be reported by calling: swi 590

.data
Harry:  .alloc  10               # allocate static space for 5 moves
Sally:  .alloc  10               # allocate static space for 5 moves

.text
WhenMet:	addi  $1, $0, Harry     # set memory base
          # addi  $2, $0, -1        # prompting for input
          swi     597             # create timelines and store them
          addi  $4, $0, 0         # initialize $4; $4 represents index counter for Harry i.e. i
          addi  $5, $0, 0         # initialize $5; $5 represents index counter for Sally i.e. j
          addi  $6, $0, 0         # initialize $6; $6 is for tracking the number of years Harry spent in each city i.e. index1
          addi  $7, $0, 0         # initialize $7; $7 is for tracking the number of years Sally spent in each city i.e. index2
          addi  $2, $0, 0         # initialize SumYears to 0

WLoop:    slti  $8, $4, 39        # is i < 10?
          slti  $9, $5, 39        # is j < 10?
          add   $10,$8, $9        # are both those conditions satisfied?
          addi  $11,$0, 2         # initialize $11 to 2 for comparison
          bne   $10,$11, End      # if both conditions are not satisfied, exit loop
          addi  $11,$0, 1         # initialize $11 to 1 for comparison later

If1:      lw    $12, Harry($4)    # read Harry[i]
          slt   $8, $6, $12       # is index1 < Harry[i]?
          beq   $8, $11, If2      # then go to the second if block
          addi  $4, $4, 8         # increment i by 2
          addi  $6, $0, 0         # index1 = 0 (reinitialization)

If2:      lw    $13, Sally($5)    # read Sally[j]
          slt   $8, $7, $13       # is index2 < Sally[j]?
          beq   $8, $11, If3      # then go to the third if block
          addi  $5, $5, 8         # increment j by 2
          addi  $7, $0, 0         # index2 = 0 (reinitialization)

If3:      addi  $18, $0, 44       # for checking boundary condition
          addi  $14, $4, 4        # $14 = i + 1
          lw    $15, Harry($14)   # read Harry[i + 1]
          beq   $18, $14, End     # exit if block if last index reached
          addi  $16, $5, 4        # $15 = j + 1
          lw    $17, Sally($16)   # read Sally[j + 1]
          bne   $15, $17, Incr    # if $15 != $16; exit the if block
          addi  $2, $2, 1         # increment SumYears

Incr:     addi  $6, $6, 1         # increment index1
          addi  $7, $7, 1         # increment index2

          j WLoop                 # loop back

End: 		swi     590		# give answer
            jr      $31             # return to caller
