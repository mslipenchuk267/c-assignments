/* Matthew Slipenchuk - tuf91673@temple.edu	
 * CS 2107, Assignment 2 Decommenter
 * This program will ask the user to enter the file name, and write its non-commented
 * contents to a file called rmcmt_output.txt 
 */
#include <stdio.h> 
#define BUFF_SIZE 64 
 
int main() { 
    FILE *fp, *fp2;
	/* State variables and line number */
    int in_comment,first_char = 1;
	size_t line_number = 1;
	char input_file[] = "test.c";
	char output_file[] = "rmcmt_output.c";
    char curr,prev;  /* Store char read from file */
  
    /* Get file name from user. User can provide 
	 * the filename if the file is in the
	 * current working directory or the full path
	 * must be provided.
	 */

  
    fp = fopen(input_file, "r"); /* Open input file */
	fp2 = fopen(output_file, "a"); /* Create output file */
	
    if (fp == NULL) { /* Does file actually exist? */
        printf("Could not open file %s", input_file); 
        return 1; 
    } 
  
    in_comment = 0;
	prev = getc(fp); /* Get first char */
	/* Iterate through every char in file until End of File (EOF) is reached */
    for (curr = getc(fp); curr != EOF; curr = getc(fp)) {
        if (curr == '*' && prev == '/') { /* Checks for "/*" */
			in_comment = 1;	/* Update state variable */
		} else if (curr == '/' && prev == '*') { /* Check for */
			in_comment = 0;    /* Update state variable */
		} else if (curr == '\n') { /* Check if about to exit comment */
			line_number++;
		} 
		
		if (in_comment = 0) {
			if (first_char == 1) { /* Write the first char (prev) on first pass if not in comment*/
				fputc(prev, fp2); 
				first_char = 0;
			}
			fputc(curr, fp2); /* Write char to file if not in comment */
		}
		prev = curr; /* Update previous char's value */
	}	

	if (in_comment == 1) {
		printf("Error: Unterminated Comment\n"); 
        return 1; 
	}
	
    fclose(fp); // Close the file 
	fclose(fp2);
    printf("The file %s has %d lines\n ", output_file, line_number); 
	
    return 0; 
}