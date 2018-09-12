#include <stdio.h>

#define LEN_A 10

/* function declarations */
void print_array(int[], int);
void reverse(int[], int);
double average(int[], int);
void insert(int[], int, int, int);
int less_than_average(int[], int);
void rotate_right(int[], int, int);
void array_copy(int[], int[], int);
void initialize(int[], int, int);
void evens_on_left(int[], int);
int find(int A[], int len, int x);
int find_last(int A[], int len, int x);
int contains_dup(int A[], int len);

int main(int argc, char **argv)
{
  int A[] = {9, 505, 321, 117, 27, 64, 13, 9, 12, 208};
  int B[LEN_A+1];
  int newValue=505;

  printf("A[] is:\n");
  print_array(A, LEN_A);

  initialize(B, LEN_A+1, 0);
  printf("B[] is:\n");
  print_array(B, LEN_A+1);

  array_copy(B, A, LEN_A);
  printf("but now it's\n");
  print_array(B, LEN_A+1);

  insert(B, newValue, 0, LEN_A+1);
  printf("and after inserting %d at the beginning it's\n", newValue);
  print_array(B, LEN_A+1);


  printf("The average of A[] is %f\n", average(A,LEN_A));
  printf("There are %d items in A[] less than this.\n", less_than_average(A,LEN_A));

  reverse(A, LEN_A);
  print_array(A, LEN_A);

  rotate_right(A, LEN_A, 3);
  print_array(A, LEN_A);

  evens_on_left(A, LEN_A);
  print_array(A, LEN_A);

  printf("The index of the first occurrence of %d is %d.\n", 9, find(A, LEN_A, 9));
  printf("The index of the last occurrence of %d is %d.\n", 9, find_last(A, LEN_A, 9));

  if (contains_dup(A, LEN_A))
    printf("A[] contains a dup\n");
  else
    printf("A[] doesn't contain a dup\n");

  if (contains_dup(B, LEN_A+1))
    printf("B[] contains a dup\n");
  else
    printf("B[] doesn't contain a dup\n");

  return 0;
}

/* functions implementation */

/* prints A[] inside parentheses with each value separated
   by commas to stdout (which will be the screen). */
void print_array(int A[], int length) {
  int i;
  printf("( ");
  for (i = 0; i < length; i++) {
    if (i < length - 1) {
      printf("%d, ", A[i]);
    } else {
      printf("%d ", A[i]);
    }
  }
  printf(")\n");
}

/* returns the average of the items in A[] or 0.0 if A is empty */
double average(int A[], int length) {
  int i, sum = 0;
  for (i = 0; i < length; i++) {
    sum += A[i];
  }
  if (sum == 0) {
    return 0.0;
  } else {
    return sum / length; /* Pf. Salvatore said it was ok to use int division */
  }
}

/* returns the number of items in A that are less than the
   average of the items in A */
int less_than_average(int A[], int length) {
   int i, count = 0;
   double avg = average(A, length);

   for (i = 0; i < length; i++) {
     if (A[i] < avg)
       count++;
   }
  return count;
}

/* Reverses the values in A[].  For example, if before the function,
   A[] contained [1,2,3,4,5], after the function, A[] contains
   [5,4,3,2,1] */
void reverse(int A[], int length) {
  int i, temp;
  for (i = 0; i < length/2; i++) {
    temp = A[i];
    A[i] = A[length-1-i];
    A[length-1-i] = temp;

  }
}

/* returns the second largest item in A[], or -1 if len < 2 */
int secondLargest(int A[], int length) {
  if (length < 2) {
    return -1;
  } else {
    int i,largest, secondLargest;
    largest = A[0];
    for (i = 1; i < length; i++) {
      if (A[i] > largest) {
        secondLargest = largest; // Assign to value of last largest value
        largest = A[i]; // Update new largest value
      }
    }
    return secondLargest;
  }
}

/* rotates the values in the array numPlaces to the right
   for example, if A[] is initially 10,20,30,40,50, and numPlaces=2
   after the function finishes, A[] would be 40,50,10,20,30 */
void rotate_right(int A[], int length, int numPlaces) {
  int i,j,last;
  for (i = 0; i < numPlaces; i++) {
    last = A[length - 1];
    for (j = length - 1; j > 0; j--) {
      A[j] = A[j-1];
    }
    A[0] = last;
  }
}

/* inserts the value n in A[] at the given index and shifts
   all other values up one position.  A[] contains length items.
   It is up to the caller to make sure that there is enough space
   in A[] to accomodate the new item, and that the index is valid. */
void insert(int A[], int n, int index, int length) {
  int i;
  for (i = length - 1; i > index; i--) {
    A[i] = A[i-1];
  }
  A[index] = n;
}

/* copies the first numItems from S to D. */
void array_copy(int D[], int S[], int numItems) {
  int i;
  for (i = 0; i < numItems; i++) {
    D[i] = S[i];
  }
}

/* sets the first len elements of A to initialValue */
void initialize(int A[], int len, int initialValue) {
  int i;
  for (i = 0; i < len; i++) {
    A[i] = initialValue;
  }
}

/* shuffles the values in A so that the even values
   are all to the left of the odd values */
void evens_on_left(int A[], int len) {
  int i,temp, counter = 0;
  for (i = len - 1; i > 0; i--) {
    if (counter < i - 1) {
      while(A[counter] % 2 == 0) { /* Skip over Even already on right*/
        counter++;
      }
      temp = A[i]; /* Swap Values */
      A[i] = A[counter];
      A[counter] = temp;
    }
  }
}

/* returns the index of the first occurrence of
 * x in A[] or -1 if x doesn't exist in A[] */
int find(int A[], int len, int x) {
  int i;
  for (i = 0; i < len; i++) {
    if (A[i] == x)
      return i;
  }
  return -1; // Only executes if x not in A
}

/* returns the index of the last occurrence of
   x in A[] or -1 if x doesn't exist in A[] */
int find_last(int A[], int len, int x) {
  int i;
  for (i = len; i > 0; i--) {
    if (A[i] == x)
      return i;
  }
  return -1; // Only executes if x not in A
}

/* returns 1 if there is at least one element in A[]
   that is contained elsewhere in A[], or 0 if there isn't */
int contains_dup(int A[], int len) {
  int i,j;
  for (i = 0; i < len; i++) {
    for (j = 1; j < len; j++) {
      if (A[i] == A[j]) // Check if values are duplicates
        return 1; // exit function as soon as duplicate is found
    }
  }
  return 0; // Only executes if no duplicate values in array
}
