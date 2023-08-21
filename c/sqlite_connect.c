#include <sqlite3.h>
#include <stdio.h>

int main(void)
{
    sqlite3* db_ptr;
    sqlite3_stmt* stmt;
    char* errMesg = 0;

    int ret = 0;

    ret = sqlite3_open("../database/sqlprogram.db", &db_ptr);

    if (ret != SQLITE_OK) {
        printf("Database opening error\n");
    }

    char* sql_stmt = "SELECT * FROM student_master";

    ret = sqlite3_prepare_v2(db_ptr, sql_stmt, -1, &stmt, 0);

    if (ret != SQLITE_OK) {
        printf("\nUnable to fetch data");
        sqlite3_close(db_ptr);
        return 1;
    }

    printf("Student details\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%s %s %s\n", sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db_ptr);

    return 0;
}
