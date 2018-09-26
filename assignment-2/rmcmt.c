/* Matthew Slipenchuk - tuf91673@temple.edu	
 * CS 2107, Assignment 2 Decommenter
 * This program will read in a file, and write its non-commented
 * contents to a file called rmcmt_temp.txt 
 */
#include <stdio.h> 
#define BUFF_SIZE 64 
 
int main() 
{ 
    FILE *fp, *fptemp;
	/* State variables and line number */
    int in_comment, out_comment,line_number = 0; 
    char file_name[BUFF_SIZE];
	char[] temp_file_name[] = "rmcmt_temp.txt";
    char c;  /* Store char read from file */
  
    /* Get file name from user. User can provide 
	 * the filename if the file is in the
	 * current working directory or the full path
	 * must be provided.
	 */
    printf("Enter file name: "); 
    scanf("%s", file_name); 
  
    fp = fopen(file_name, "r"); /* Open file */
	fp2 = fopen(temp_file_name, "a");
	
    if (fp == NULL) { /* Does file actually exist? */
        printf("Could not open file %s", file_name); 
        return 1; 
    } 
  
    /* Iterate through every char in file until End of File (EOF) is reached */
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') {
            line_number = line_number + 1; /* Update line_number */ 
		}
		else if (c == '/*') { /* Check if about to enter comment */
			out_comment = 0;  /* Update state variables */
			in_comment = 1;
		}
		else if (c == '*/') { /* Check if about to exit comment */
			out_comment = 1;  /* Update state variables */
			in_comment = 0;
		}
		if (out_comment = 1 && c != '*/') {
			fputc(c, fptemp);
		}
	}	

	
	if (in_comment == 1) {
		printf("Error: Unterminated Comment\nLine: %d", line_number); 
        return 1; 
	}
	
    fclose(fp); // Close the file 
	remove(file_name); /* Delete old, comment ridden, file */
	rename(tempfile_name, file_name); /* Rename our output file */
	fclose(fptemp);
    printf("The file %s has %d lines\n ", file_name, count); 
	
    return 0; 
} 
