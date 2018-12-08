#include <stdio.h>
#include <string.h>
#include "db_helper.h"
#include "sqlite3.h"

int main(int argc, char **argv) {
	create_db("my_database.db");
	return 0;
}
