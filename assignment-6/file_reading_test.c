#include <string.h>
#include <stdio.h>
#include "sqlite3.h" 
/* int populate_table (char *filename, char *sql_name){ */
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


int main ( void ){
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;

	/* Open database */
	rc = sqlite3_open("my_database.db", &db);

	if( rc ) {
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  return(0);
	} else {
	  fprintf(stderr, "Opened database successfully\n");
	}
	
	/* Create SQL statement */
	sql = "CREATE TABLE PERSON_IDS("  \
	  "TUID         CHAR(9) PRIMARY KEY	NOT NULL," \
	  "ACCESSNET    CHAR(8)			    NOT NULL );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Tables created successfully\n");
	}
	
	static const char filename[] = "person_ids";
    FILE *file = fopen ( filename, "r" );
	int onHeader = 1;
	char command[] = "INSERT INTO ";
	char comma[] = ",";
	char comma_single_quote[] = "', '";
	char seperator[] = "'";
	char end_command[] = ")";
	char end_values[] = "' );";
	
	strupr(filename);
	strcat(command, filename);
	strcat(command, " (");
    if (file != NULL) {
		char line[256];
		char *sql; /* SQL statement string */
		while ( fgets ( line, sizeof line, file ) != NULL ) {	/* read line from file*/
			char delims[] = "#,\n";
			//char result[] = "INSERT INTO PERSON_IDS (TUID,ACCESSNET) VALUES ('";
			char values[] = " VALUES ('";
			char* token;
			if ( onHeader ) {
				token = strtok(line, delims);
				while(token) {
					//strcat(result, seperator);
					strcat(command, token);
					//strcat(result, seperator);
					token = strtok(NULL, delims); /* New token */
					if (token != NULL) {	
						strcat(command, comma);
					} else {
						strcat(command, end_command);
					}
				}
				onHeader = 0;
				continue;	/* Skip header line in file */
			}
			
			token = strtok(line, delims);
			while(token) {
				//strcat(result, seperator);
				strcat(result, token);
				//strcat(result, seperator);
				token = strtok(NULL, delims); /* New token */
				if (token != NULL) {	
					strcat(result, comma_single_quote);
				} else {
					strcat(result, end_values);
				}
			}
			printf("%s\n", result);
			
			strcat(command,values);
			
			sql = command;
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			} else {
			  fprintf(stdout, "Records created successfully\n");
			}
			
		}
    fclose(file);
	sqlite3_close(db);
    }
    else{
		perror(filename); /* Error message */
    }
	
	
   return 0;
}