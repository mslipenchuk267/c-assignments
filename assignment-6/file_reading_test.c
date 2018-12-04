#include <stdio.h>
#include <string.h>
#include <ctype.h>
/* int populate_table (char *filename, char *sql_name){ */

int tokenIsNumber(char *token);

int tokenIsNumber(char *token) { 
	int i;
	int len = strlen(token);
    for (int i = 0; i < len; i++) 
        if (~isdigit(token[i])) 
            return 0; /* 0 - false */
  
    return 1; /* 1 - true */
} 

int main ( void ){
	static const char filename[] = "person_ids";
    FILE *file = fopen ( filename, "r" );
	int onHeader = 1;
	char comma[] = ", ";
	char end_statement[] = " );";
	
    if (file != NULL) {
		char line[ 128 ];
		char *sql; /* SQL statement string */
		while ( fgets ( line, sizeof line, file ) != NULL ){	/* read line from file*/
			if ( onHeader ) {
				onHeader = 0;
				continue;	/* Skip header line in file */
			}
			char delims[] = "#,\n";
			char result[] = "VALUES (";
			char* token;
			token = strtok(line, delims);
			while(token) {
				// Prepare token for sql statement
				// ex. John must be in form of 'John' as per SQlite syntax
				if (~tokenIsNumber(token)) {
					strcat("'", token);
					strcat(token, "'");
				}

				strcat(result, token);
				token = strtok(NULL, delims); /* New token */
				if (token != NULL) {	
					strcat(result, comma);
				} else {
					strcat(result, end_statement);
				}
			}
			printf("%s\n", result);			
		}
    fclose(file);
    }
    else{
		perror(filename); /* Error message */
    }
    return 0;
}

