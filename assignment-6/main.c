#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include "db_helper.h"

int main ( void ){
	create_db("my_database.db");
	return 0;
}
