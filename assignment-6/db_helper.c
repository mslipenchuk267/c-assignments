#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "db_helper.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

// Returns true if s is a number else false 
bool tokenIsNumber(char *token) { 
    for (int i = 0; i < s.length(); i++) 
        if (isdigit(s[i]) == false) 
            return false; 
  
    return true; 
} 

int create_db(char *filename) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("test.db", &db);

	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return 0;
	} else {
		fprintf(stderr, "Opened database successfully\n");
	}
	sqlite3_close(db);
	return 0;
}

int create_tables(char *filename) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;

	/* Open database */
	rc = sqlite3_open("myDatabase.db", &db);

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
	  "PREFERRED_NAME TEXT    			  NOT NULL," );";

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
	  "ROLE_EXP_DATE INT			    NOT NULL );";

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