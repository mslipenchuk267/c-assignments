#include <stdio.h>
#include <string.h>
/* int populate_table (char *filename, char *sql_name){ */
int main ( void ){
	static const char filename[] = "person_ids";
    FILE *file = fopen ( filename, "r" );
	int onHeader = 1;
	
    if (file != NULL) {
		char line[ 128 ];
		char *sql; /* SQL statement strinf */
		while ( fgets ( line, sizeof line, file ) != NULL ){	/* read line from file*/
			if ( onHeader ) {
				onHeader = 0;
				continue;	/* Skip header line in file */
			}
			char delims[] = "#";
			char result[] = "VALUES (";
			char* token;
			token = strtok(line, delims);
			while(token != NULL) {
				strcat(result, token);
				token = strtok(NULL, delims);
			}
			printf("%s", result);			
		}
    fclose(file);
    }
    else{
		perror(filename); /* Error message */
    }
    return 0;
}