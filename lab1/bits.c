/* 
 * CS:APP Data Lab 
 * 
 * Rishabh Jain - 604817863
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /*
  inverts the bits first. And then adds 1. If x was 0, then this will
  become 0. using & with 1 at end will only activate LSB, which is 0.
  hence, this will return 0 for x = 0 and 1 for x > 0 and x < 0.  
  */
  int invx = ~x;
  int negx = invx + 1;
  return ((~negx & invx) >> 31) & 1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
/*
  Firstly, we shift the bits of x by 1 to the right and then
  set all the even numbered bits to 0. Then, we invert this and add
  1 to effectively get the negative value, which we then add to the 
  original x. This basically means that we're getting the difference
  of the original x and the 1-rightshifted x with even bit deactivated.
  By doing this, we get the number bits in a two bit number.
  Then, we throw away every 2nd two bit counts and do it again after
  shifting by 2. We've effectively taken the bitcount of the lowest two
  and the 2nd lowest two and added them together to get the bitcount of
  the lowest four bits.
  We basically repeat the same concept, but add 4 bit counts this time.
  By repeating this method, we get the sum of all the activated bits.
*/
    
    //first we create the masks
    
    int firsts = 0x55 + (0x55 << 8 ) + (0x55 << 16) + (0x55 << 24); // 01010101...
    int seconds = 0x33 + (0x33 << 8 ) + (0x33 << 16) + (0x33 << 24); // 00110011...
    int thirds = 0x0f + (0x0f << 8 )  + (0x0f << 16) + (0x0f << 24); // 00001111...
    int fourths = 0xff + (0xff << 16); // 0000000011111111...
    int fifths = 0xff + (0xff << 8); // 00000000000000001111111...
    
    // We now add the zeros and shift right so we can get the
    // correct sum in one integer
    
    int sum = (x & firsts) + ((x >> 1) & firsts);
    sum = (sum & seconds) + ((sum >> 2) & seconds);
    sum = (sum + (sum >> 4)) & thirds ;
    sum = (sum + (sum >> 8)) & fourths ;
    sum = (sum + (sum >> 16)) & fifths ;
    
    return sum;
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
/*
Using the first De Morgan's Law, we have the following result
*/

  return ~(~x & ~y);
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
/*
 First we need to deactivate all the unnecessary bits in x.
 We do this by creating a mask which only has n LSB bits activated.
 Then, we & it with x to successfully have only the bits required to 
 repeat in x. 
 
 The main strategy to create the required word is to move the bits
 to the left and then add more bits to the vacated bit spaces.
 We do this 5 times because if n = 1, we will need to shift left
 5 times. Basically, we move the bits to the left by the length
 of the bits to be added. Then we add the bits by using |. Finally
 for the next iteration, we set x = y, so that we need less 
 iterations.

 However, this calls for the problem of shifting by a value larger
 than the word size. We accomodate for this by using the checker
 variable. The aim is to have checker set to -1 if n < 32 else it
 is 0. We & n with checker before shifting so that it becomes 0 
 if shifting would give undefined behaviour. We get the checker
 by using division. If n is less than 32, then value becomes 0, else
 it is 1 or greater than 1. By banging it, if n is less than 32
 then value becomes 1, else it becomes 0. Then we take negative of
 the value, hence finally checker becomes -1 if n is less than 32
 and 0 otherwise.
*/
  int mask = (~0 << (n-1));
  mask <<= 1;
  mask = ~mask; 
  x = x & mask;
  int y = x;
 
  int checker = -!(n/32);
  x <<= n & checker;
  y = x | y;
  x = y;
  n = n * 2;
  
  checker = -!(n/32);
  x <<= n & checker;
  y = x | y;
  x = y;
  n = n * 2;
  
  checker = -!(n/32);
  x <<= n & checker;
  y = x | y;
  x = y;
  n = n * 2;
  
  checker = -!(n/32);
  x <<= n & checker;
  y = x | y;
  x = y;
  n = n * 2;
  
  checker = -!(n/32);
  x <<= n & checker;
  y = x | y;

  return y;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
/* 
 first we calculate how many high order bits are remaining after
 using n low order bits. Then we fill the high order bits with the 
 same value as the sign bit of x. Then we check whether we were
 successful in recreating the number or not using !(NEW ^ x).
*/
 int r, c;
 c = 33+ ~n;
 r = !(((x << c) >> c) ^ x);
 return r; 
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
/* 
  multiply n by 8 to get number of bits. Do the required
  shift to get the required bits at the LSB positions. 
  Create a mask which can deactivate all bits except the 
  required ones and & it with x. Then return x.

*/
 int mask = ~(~0 << 8);
 n<<=3;
  return (x>>n) & mask;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
/* 
  Main strategy is to subtract the numbers and see if the answer is
  negative. We subtract by converting one number to negative by
  inverting it and adding one, and then adding that to the other 
  number. We move the MSB to the LSB position and then deactivate
  all the other bits. The answer we have now tells us whether the 
  y number is greater than x. To give the correct output, we bang
  it. But we also need to account for the corner case of x being
  T_MIN. We do that by performing a set of operations which would
  cause our final mask to be 1 if x is that value and 0 otherwise.
*/

/*
  ATTEMPT 1
  int z = !(~((~x << 1) | 1));
  return (!(((y+((~x)+1))>>31)&1)) | z;
 
 But this doesn't work properly because of overflow.
 We account for that by separating the sign and the difference.
*/

  int sign, isLess, dif, equal, isLessorEqual;

  sign = x ^ y;
  isLess = ~sign;
  dif = y + (~x + 1);

  equal = !dif;

  sign = sign & x;
  
  dif = ~dif;
  
  isLess = isLess & dif;
  isLess = isLess | sign;
  isLess = isLess & (1 << 31);

  isLessorEqual = (!!isLess) | (equal);

  return isLessorEqual;  
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {

 /*
  First, we deactivate all the bits except the MSB by using & on x
  and the mask 100000... Then we | it with !x to check if x is 0.
  The result we get tells us whether the number is negative or 0,
  so we toggle it by bang to tell us whether it is positive or not.
 */
    
  return !((x&(1<<31)) | !x);
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
/* 
   for successfully performing logical shift for n > 0, we need
   to convert the MSB to 0 and then perform normal right shift.
   But if n is 0, then we should retain the original MSB.

   So we create the mask by using tester. We activate all the bits
   except LSB and | it with (!n), which sets the required bit at 
   the LSB position.
   To move it where we need it to be, we left shift it by 32.
   Finally, we & with the mask, and move the bits where 
   they need to be.
*/
  
  int tester = !n;
  tester <<= 31;
  int tempMask = ~(~0 << 31);
  //tester = tester | tempMask;
  int secondMask = tempMask;  
  secondMask >>= n;
  secondMask = secondMask | (1 << (31 + ~n + 1));
  secondMask = secondMask | tester;
  x >>= n;
  x = x & secondMask;
  return x;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
/*
 0 in binary is all unactivated bits
 ~0 has all its bits activated and is -1 in decimal
 Shifting left by 31 bits makes the number 10000... thus resulting
 in the minimum integer required.
*/

  return ~0 << 31;
}
