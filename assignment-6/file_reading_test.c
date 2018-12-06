#include <stdio.h>
#include <string.h>
/* int populate_table (char *filename, char *sql_name){ */
int main ( void ){
	static const char filename[] = "person_ids";
    FILE *file = fopen ( filename, "r" );
	int onHeader = 1;
	char comma[] = ", ";
	char single_quote[] = "'";
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
				starcat(result, "'");
				strcat(result, token);
				starcat(result, "'");
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