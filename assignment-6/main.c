#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db_helper.h"
#include "sqlite3.h"

/*
 Matthw Slipenchuk - tuf91673@temple.edu
 Assignment 6 - All Records at once option. 
 - To compile: gcc -pthread -o main main.c db_helper.c sqlite3.c -ldl
 - To run: main
 - To check person_resources for correct output: cat person_resources
 - Before running again: rm main my_database.db 
						 Replace person_resource with header only
 */
int main(int argc, char **argv) {
	create_db("my_database.db");
	create_tables("my_database.db");
	populate_table_from_file("my_database.db","resources","INSERT INTO RESOURCES (ID,NAME) VALUES ('");
	populate_table_from_file("my_database.db","person_roles","INSERT INTO PERSON_ROLES (TUID,ROLE_ID,ROLE_EXP_DATE) VALUES ('");
	populate_table_from_file("my_database.db","resources_roles","INSERT INTO RESOURCES_ROLES (RESOURCE_ID,ROLE_ID) VALUES ('");
	populate_person_resources("my_database.db");
	
	return 0;
}
