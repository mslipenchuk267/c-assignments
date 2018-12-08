#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sqlite3.h" 
#include "db_helper.h"

/* Prints out all Entries */
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int create_db(char* dbname) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open(dbname, &db);

	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return 0;
	} else {
		fprintf(stderr, "Opened database successfully\n");
	}
	sqlite3_close(db);
	return 0;
}

int create_tables(char *dbname) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	/* Open database */
	rc = sqlite3_open(dbname, &db);
	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} else {
		fprintf(stdout, "Opened database successfully\n");
	}
	/* Create SQL statement */
	sql = "CREATE TABLE PERSON_NAMES("  \
	  "TUID			  CHAR(9) PRIMARY KEY NOT NULL," \
	  "GIVEN_NAME     TEXT    		      NOT NULL," \
	  "MIDDLE_NAME	  TEXT    			  NOT NULL," \
	  "SURNAME        TEXT    			  NOT NULL," \
	  "PREFERRED_NAME TEXT			      NOT NULL );";
	  
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE PERSON_IDS("  \
	  "TUID         CHAR(9) PRIMARY KEY	NOT NULL," \
	  "ACCESSNET    CHAR(8)			    NOT NULL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE PERSON_ROLES("  \
	  "TUID          CHAR(9) PRIMARY KEY	NOT NULL," \
	  "ROLE_ID       INT             		NOT NULL," \
	  "ROLE_EXP_DATE INT			    	NOT NULL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE PERSON_RESOURCES("  \
	  "TUID         CHAR(9) PRIMARY KEY	NOT NULL," \
	  "RESOURCE     CHAR(8)			    NOT NULL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE RESOURCE("  \
	  "ID 		 INT    PRIMARY KEY	NOT NULL," \
	  "NAME      CHAR(6)			NOT NULL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE RESOURCE_ROLES("  \
	  "RESOURCE_ID INT    PRIMARY KEY	NOT NULL," \
	  "ROLE_ID     INT				    NOT NULL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE RESOURCE_REQUIREMENTS("  \
	  "RESOURCE_ID 		  INT     PRIMARY KEY NOT NULL," \
	  "PERSON_NAME_TYPE   CHAR(9)     		  NOT NULL," \
	  "PERSON_ID_TYPE     CHAR(9)		   	  NOT NULL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Tables created successfully\n");
	}
	sqlite3_close(db);
	return 0;
}

int populate_table_from_file(char *dbname, char *filename, char *sql_command) {
	//"INSERT INTO PERSON_IDS (TUID,ACCESSNET) VALUES ('"
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	
	/* Open database */
	rc = sqlite3_open(dbname, &db);

	if( rc ) {
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  return(0);
	} else {
	  fprintf(stderr, "Opened database successfully\n");
	}
	
	//static const char filename[] = "person_ids";
    FILE *file = fopen ( filename, "r" );
	int onHeader = 1;
	char *result;
	char comma[] = "', '";
	char seperator[] = "'";
	char end_statement[] = "' );";
	
    if (file != NULL) {
		char line[256];
		char *sql; /* SQL statement string */
		while ( fgets ( line, sizeof line, file ) != NULL ) {	/* read line from file*/
			if ( onHeader ) {
				onHeader = 0;
				continue;	/* Skip header line in file */
			}
			char delims[] = "#,\n";
			result = (char *)malloc(strlen(sql_command));
			strcpy(result,sql_command);
			char* token;
			token = strtok(line, delims);
			while(token) {
				//strcat(result, seperator);
				strcat(result, token);
				//strcat(result, seperator);
				token = strtok(NULL, delims); /* New token */
				if (token != NULL) {	
					strcat(result, comma);
				} else {
					strcat(result, end_statement);
				}
			}
			printf("%s\n", result);
			
			sql = result;
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			} else {
			  fprintf(stdout, "Records created successfully\n");
			}
			free(result);
		}
    fclose(file);
	sqlite3_close(db);
    }
    else{
		perror(filename); /* Error message */
    }
	
   return 0;
} 