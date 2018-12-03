#include <stdio.h>
/* int populate_table (char *filename, char *sql_name){ */
int populate_table ( void ){
	static const char filename[] = "person_ids";
    FILE *file = fopen ( filename, "r" );
	int onHeader = 1;
	
    if (file != NULL) {
		char line [ 128 ];
		char *sql; /* SQL statement strinf */
		while ( fgets ( line, sizeof line, file ) != NULL ){	/* read line from file*/
			if ( onHeader ) {
				onHeader = 0;
				continue;	/* Skip header line in file */
			}
			fputs ( line, stdout );		/* write line from file */
			char str[] = line; 
			char sql_values[ ] = "VALUES (" ;	/* "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );" */
			char* token = strtok(str, "#");		/* Return 1st token */
			
			strcat ( sql_values, token );
			strcat( sql_values, "," );
			
			while (token != NULL) {		/* Print tokens while delimiter present in str[] */
				strcat ( sql_values, token );
				printf("%s\n", token); 				
				strcat( sql_values, ", " );
				token = strtok(NULL, "#");		/* retreieve next token */
			}
			
			int len = strlen(sql_values);
			sql_values[len-2] = '\0';			/* Remove last ", " from string" */
			strcat( sql_values, " );" );
			printf("%s\n", sql_values); 	
		}
    fclose(file);
    }
    else{
		perror(filename); /* Error message */
    }
    return 0;
}