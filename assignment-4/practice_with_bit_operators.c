#include <stdio.h>

unsigned int add(unsigned int, unsigned int);
unsigned int sub(unsigned int, unsigned int);
unsigned int mul(unsigned int, unsigned int);
unsigned int lt(unsigned int, unsigned int);
unsigned int gt(unsigned int, unsigned int);
unsigned int getByte(unsigned int, unsigned int);

int main(int argc, char **argv)
{

	unsigned int i, j;

	printf("Enter an integer ");

	scanf("%u", &i);
	printf("\nEnter another integer ");
	scanf("%u", &j);
	printf("\ni + j = %u\n", add(i,j));
	printf("\ni - j = %u\n", sub(i,j));
	printf("\ni * j = %u\n", mul(i,j));
	printf("i > j = %s\n", (gt(i,j) ? "TRUE" : "FALSE"));
	printf("i < j = %s\n", (lt(i,j) ? "TRUE" : "FALSE"));
	printf("jth byte of i = %ux\n", getByte(i,j));

	return 0;
}

unsigned int add(unsigned int i, unsigned int j)
{
/* can be done in a total of 7 lines, including one to declare an unsigned int, */
/* two for a while loop, and one for the return */
    while (y != 0) {
        unsigned int carry = x & y;

        x = x ^ y; 

        y = carry << 1;
    }
    return x;
	// return i + j;
}

unsigned int sub(unsigned int i, unsigned int j)
{
/* Similar 7 lines, although there is a shorter way */
	// Iterate till there is no carry 
    while (y != 0) 
    { 
        // borrow contains common  
        // set bits of y and unset 
        // bits of x 
        int borrow = (~x) & y; 
        // Subtraction of bits of x  
        // and y where at least one 
        // of the bits is not set 
        x = x ^ y; 
        // Borrow is shifted by one  
        // so that subtracting it from 
        // x gives the required sum 
        y = borrow << 1; 
    } 
    return x; 
	//return i - j;
}

unsigned int mul(unsigned int i, unsigned int j)
{
/* can be done in a total of 8 lines including one to declare unsigned ints */
/* two for a for loop, and one for the return */
	return i * j;
}

/* returns non-zero if i is less than j or zero otherwise */
unsigned int lt(unsigned int i, unsigned int j)
{
	if (i < j) { 
		return 1;
	}
	else {
		return 0;
	}
}

/* returns non-zero if i is greater than j or zero otherwise */
unsigned int gt(unsigned int i, unsigned int j)
{
	if (i > j) { 
		return 1;
	}
	else {
		return 0;
	}
}

/* returns the jth byte of i */
unsigned int getByte(unsigned int i, unsigned int j)
{
	
}