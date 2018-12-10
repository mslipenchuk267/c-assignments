#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sqlite3.h" 
#include "db_helper.h"
#define MAX 256

/* Prints and formats entries for logging purposes */
static int callback_log(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   char *result;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
/* Prints and formats entries for displaying all records to user */
static int callback_display_result(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}
/* Writes entries to file, hash delimited */
static int callback_write_to_file(void *data, int argc, char **argv, char **azColName){
	int i;
	char *result;
	FILE *fp;
	
	fp = fopen("aa", "a");
	for(i = 0; i<argc; i+=2){
		result = (char *)malloc(11);
		strcpy(result,argv[i] ? argv[i] : "NULL");
		strcat(result,"#");
		strcat(result, argv[i++] ? argv[i++] : "NULL");
		strcat(result,"\n");
		fputs(result,fp);
		free(result);
	} 
	fclose(fp);
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
	rc = sqlite3_exec(db, sql, callback_log, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE PERSON_IDS("  \
	  "TUID         CHAR(9) PRIMARY KEY	NOT NULL," \
	  "ACCESSNET    CHAR(8)			    NOT NULL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback_log, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE PERSON_ROLES("  \
	  "TUID          CHAR(9)             	NOT NULL," \
	  "ROLE_ID       TEXT   	            NOT NULL," \
	  "ROLE_EXP_DATE TEXT			    	NOT NULL," \
	  "PRIMARY KEY (TUID,ROLE_ID));";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback_log, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE PERSON_RESOURCES("  \
	  "TUID         CHAR(9) PRIMARY KEY	NOT NULL," \
	  "RESOURCE     CHAR(8)			    NOT NULL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback_log, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE RESOURCES("  \
	  "ID 		 TEXT    PRIMARY KEY	NOT NULL," \
	  "NAME      CHAR(6)			NOT NULL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback_log, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE RESOURCES_ROLES("  \
	  "RESOURCE_ID TEXT		NOT NULL," \
	  "ROLE_ID 	   TEXT		NOT NULL," \
	  "PRIMARY KEY (RESOURCE_ID,ROLE_ID));";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback_log, 0, &zErrMsg);
	/* Create SQL statement */
	sql = "CREATE TABLE RESOURCE_REQUIREMENTS("  \
	  "RESOURCE_ID 		  TEXT    PRIMARY KEY NOT NULL," \
	  "PERSON_NAME_TYPE   CHAR(9)     		  NOT NULL," \
	  "PERSON_ID_TYPE     CHAR(9)		   	  NOT NULL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback_log, 0, &zErrMsg);
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
	  fprintf(stderr, "Created database successfully\n");
	}
	
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
			result = (char *)malloc(MAX);
			strcpy(result,sql_command);
			char* token;
			token = strtok(line, delims);
			while(token) {
				strcat(result, token);
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
			rc = sqlite3_exec(db, sql, callback_log, 0, &zErrMsg);

			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			} else {
			  fprintf(stdout, "Record created successfully\n");
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

int populate_person_resources(char *dbname) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Record";

	/* Open database */
	rc = sqlite3_open(dbname, &db);

	if( rc ) {
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  return(0);
	} else {
	  fprintf(stderr, "Opened database successfully\n");
	}

	/* Create SQL statement for displaying records to user*/
	sql = "SELECT DISTINCT P.TUID, RR.RESOURCE_ID, A.NAME FROM PERSON_ROLES P " \
			"JOIN RESOURCES_ROLES RR ON P.ROLE_ID = RR.ROLE_ID " \
			"JOIN RESOURCES A ON  A.ID = RR.RESOURCE_ID";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback_display_result, (void*)data, &zErrMsg);

	if( rc != SQLITE_OK ) {
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	} else {
	  fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	return 0;

	/* Create SQL statement for writing to file*/
	sql = "SELECT DISTINCT P.TUID, RR.RESOURCE_ID FROM PERSON_ROLES P " \
			"JOIN RESOURCES_ROLES RR ON P.ROLE_ID = RR.ROLE_ID";

	rc = sqlite3_exec(db, sql, callback_write_to_file, (void*)data, &zErrMsg);

	if( rc != SQLITE_OK ) {
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	} else {
	  fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	return 0;
}