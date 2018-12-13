#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sqlite3.h" 
#include "db_helper.h"
#define MAX 256

/*
 This file is essentially a collection of wrapper functions for the SQLIte3 
 interface. It also has overiden callback functions.
 */

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
	FILE *fp;
	int i;
	char *result;
	
	fp = fopen("testing_file", "a"); /* Open output file in append mode*/
	for(i = 0; i<argc; i+=2){ /* Increment by 2 due to {tuid,resource_id,tuid,resource_id,...} order */
		result = (char *)malloc(11); /* Allocate space for line */
		strcpy(result,argv[i] ? argv[i] : "NULL"); /* Get tuid */
		strcat(result,"#");
		strcat(result, argv[i++] ? argv[i++] : "NULL"); /* Get corresponding resource_id */
		strcat(result,"\n");
		fputs(result,fp); /* write line to person_roles*/
		free(result); /* Free memory of written line*/
	}
	fclose(fp);
	return 0;
}

/* Creates .db file */
int create_db(char* dbname) {
	/* SQLite database Initalization */
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	/* Create/Open database */
	rc = sqlite3_open(dbname, &db);

	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return 0;
	} else {
		fprintf(stderr, "Created database successfully\n");
	}
	sqlite3_close(db);
	return 0;
}

/* Initalizes needed tables */
int create_tables(char *dbname) {
	/* SQLite database Initalization */
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	/* Open database */
	rc = sqlite3_open(dbname, &db);
	/* Status */
	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} else {
		fprintf(stdout, "Opened database successfully\n");
	}
	
	/* Create SQL statement - PERSON_ROLES table */
	sql = "CREATE TABLE PERSON_ROLES("  \
	  "TUID          CHAR(9)	NOT NULL," \
	  "ROLE_ID       TEXT       NOT NULL," \
	  "ROLE_EXP_DATE TEXT		NOT NULL," \
	  "PRIMARY KEY (TUID,ROLE_ID));";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback_log, 0, &zErrMsg);
	/* Create SQL statement  - RESOURCES table */
	sql = "CREATE TABLE RESOURCES("  \
	  "ID 	TEXT    PRIMARY KEY	NOT NULL," \
	  "NAME CHAR(6)				NOT NULL );";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback_log, 0, &zErrMsg);
	/* Create SQL statement - RESOURCES_ROLES table */
	sql = "CREATE TABLE RESOURCES_ROLES("  \
	  "RESOURCE_ID TEXT		NOT NULL," \
	  "ROLE_ID 	   TEXT		NOT NULL," \
	  "PRIMARY KEY (RESOURCE_ID,ROLE_ID));";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback_log, 0, &zErrMsg);
	/* Status */
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
	/* SQLite database Initalization */
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	
	/* Open database */
	rc = sqlite3_open(dbname, &db);
	/* Status */
	if( rc ) {
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  return(0);
	} else {
	  fprintf(stderr, "Opened database successfully\n");
	}
	/* File Initalization */
    FILE *file = fopen ( filename, "r" );
	int onHeader = 1;
	char *result;
	/* Used for formating SQL Statement */
	char comma[] = "', '"; 
	char seperator[] = "'";
	char end_statement[] = "' );";
	
    if (file != NULL) {
		char line[256];
		char *sql; /* SQL statement string Initalization */
		while ( fgets ( line, sizeof line, file ) != NULL ) {	/* read line from file */
			if ( onHeader ) {
				onHeader = 0;
				continue;	/* Skip header line in file */
			}
			char delims[] = "#,\n";
			result = (char *)malloc(MAX); /* Create SQL Statment */
			strcpy(result,sql_command);
			char* token;
			token = strtok(line, delims); /* Get first token */
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
			/* Status */
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			} else {
			  fprintf(stdout, "Record created successfully\n");
			}
			free(result); /* Free memory of now executed SQL statment */
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
	/* SQLite database Initalization */
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Record";

	/* Open database */
	rc = sqlite3_open(dbname, &db);
	/* Status */
	if( rc ) {
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  return(0);
	} else {
	  fprintf(stderr, "Opened database successfully\n");
	}
	
	/* Create SQL statement - Get all tuids with corresponding resource_ids and resource names */
	sql = "SELECT DISTINCT P.TUID, RR.RESOURCE_ID, A.NAME FROM PERSON_ROLES P " \
			"JOIN RESOURCES_ROLES RR ON P.ROLE_ID = RR.ROLE_ID " \
			"JOIN RESOURCES A ON  A.ID = RR.RESOURCE_ID";

	/* Execute SQL statement - Passing callback_display_result function*/
	rc = sqlite3_exec(db, sql, callback_display_result, (void*)data, &zErrMsg);

	/* Create SQL statement - Get all tuids with corresponding resource_ids */
	sql = "SELECT DISTINCT P.TUID, RR.RESOURCE_ID FROM PERSON_ROLES P " \
			"JOIN RESOURCES_ROLES RR ON P.ROLE_ID = RR.ROLE_ID";
	/* Execute SQL statment - Passing callback_write_to_file function */
	rc = sqlite3_exec(db, sql, callback_write_to_file, (void*)data, &zErrMsg);
	/* Status */
	if( rc != SQLITE_OK ) {
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	} else {
	  fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	return 0;
}