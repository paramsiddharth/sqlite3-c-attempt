#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sqlite3.h>

#ifdef _WIN32
	#define SEPARATOR '\\'
	#include <direct.h>
	#define getcwd _getcwd
#else
	#define SEPARATOR '/'
	#include <unistd.h>
	#define getcwd getcwd
#endif

#define MAX_STRING_SIZE 2048

#define CHECK_SUCCESS if (success != SQLITE_OK) \
		return 1;

int main(int argc, char* argv[]) {
	printf("FILENAME_MAX: %d\n", FILENAME_MAX);
	char* filename = "db.sqlite3";
	char* cwd = getcwd(NULL, 0);

	char dbpath[MAX_STRING_SIZE];
	sprintf(dbpath, "%s%c%s", cwd, SEPARATOR, filename);

	printf("%s\n", dbpath);

	sqlite3* db;
	int success = sqlite3_open(dbpath, &db);

	CHECK_SUCCESS

	printf("%s successfully opened!\n", filename);

	char* err;
	success = sqlite3_exec(db, (
		"CREATE TABLE IF NOT EXISTS people (\n"
		"	id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
		"	name VARCHAR(30)\n"
		");"
	), NULL, 0, &err);
	sqlite3_free(err);

	CHECK_SUCCESS

	char* people[] = {
		"Param",
		"Mukul",
		"Ritesh",
		"Yaswanth"
	};
	for (int i = 0; i < 4; i++) {
		success = sqlite3_exec(db, (
			sqlite3_mprintf(
				"INSERT INTO people (name) VALUES\n"
				"('%q');",
				people[i]
			)
		), NULL, 0, &err);
		sqlite3_free(err);

		CHECK_SUCCESS
	}

	sqlite3_close(db);

	return 0;
}
