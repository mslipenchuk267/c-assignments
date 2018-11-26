#include <stdio.h>      // printf
#include <SQLite.h>     // SQLite header (from /usr/include)

int main()
{
    Connection connection ("Users.db");
	
	Execute(connection, "create table Users (Name, Age)");
	
	for (Row const & row : Statement(connection, "select Name, Age from Users")){
		printf("%s - %d\n", row.GetString(0), row.GetString(0));
	}
}