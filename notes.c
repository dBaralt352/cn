//
// Created by dbaralt on 5/12/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notes.h"

void print_note(Note* note)
{
    printf(YELLOW "[%ld] - " GREEN "%s\n" RESET "\t%s\n\n", note->id, note->title, note->content);
}

sqlite3* load_notes(const char* database)
{
    sqlite3* db = NULL;
    char *zErrMsg = NULL;
    if (sqlite3_open(database, &db))
    {
        printf(RED "[ERR] Cant open database: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    const char* query = "CREATE TABLE IF NOT EXISTS Notes ("
                        "Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                        "Title TEXT NOT NULL,"
                        "Content TEXT NOT NULL,"
                        "Deleted BOOLEAN DEFAULT FALSE);";

    if (sqlite3_exec(db, query, NULL, NULL, &zErrMsg) != SQLITE_OK)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    return db;
}

void list_notes(sqlite3* db)
{
    const char* query = "SELECT Id, Title, Content FROM Notes WHERE Deleted = FALSE";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Note note;
        note.id = sqlite3_column_int64(stmt, 0);
        strncpy(note.title, (const char*)sqlite3_column_text(stmt, 1), sizeof(note.title) - 1);
        strncpy(note.content, (const char*)sqlite3_column_text(stmt, 2), sizeof(note.content) - 1);
        note.title[sizeof(note.title) - 1] = '\0';
        note.content[sizeof(note.content) - 1] = '\0';
        print_note(&note);
    }
    sqlite3_finalize(stmt);
}

void list_all_notes(sqlite3* db)
{
    const char* query = "SELECT Id, Title, Content FROM Notes";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Note note;
        note.id = sqlite3_column_int64(stmt, 0);
        strncpy(note.title, (const char*)sqlite3_column_text(stmt, 1), sizeof(note.title) - 1);
        strncpy(note.content, (const char*)sqlite3_column_text(stmt, 2), sizeof(note.content) - 1);
        note.title[sizeof(note.title) - 1] = '\0';
        note.content[sizeof(note.content) - 1] = '\0';
        print_note(&note);
    }
    sqlite3_finalize(stmt);
}

void delete_note(sqlite3* db,const long id)
{
    const char* query = "UPDATE Notes SET Deleted = True WHERE Id = :id";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    const int param_index = sqlite3_bind_parameter_index(stmt, ":id");
    if (param_index == -1)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_bind_int64(stmt, param_index, id);
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    sqlite3_finalize(stmt);
}

void get_note(sqlite3* db, long id)
{
    const char* query = "SELECT Id, Title, Content FROM Notes WHERE Id = :id";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    const int param_index = sqlite3_bind_parameter_index(stmt, ":id");
    if (param_index == -1)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_bind_int64(stmt, param_index, id);
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Note note;
        note.id = sqlite3_column_int64(stmt, 0);
        strncpy(note.title, (const char*)sqlite3_column_text(stmt, 1), sizeof(note.title) - 1);
        strncpy(note.content, (const char*)sqlite3_column_text(stmt, 2), sizeof(note.content) - 1);
        note.title[sizeof(note.title) - 1] = '\0';
        note.content[sizeof(note.content) - 1] = '\0';
        print_note(&note);
    }
    sqlite3_finalize(stmt);
}

void create_note(sqlite3* db, const Note* note)
{
    const char* query = "INSERT INTO Notes(Title, Content) VALUES (:title, :content)";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    int param_index = sqlite3_bind_parameter_index(stmt, ":title");
    if (param_index == -1)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_bind_text(stmt, param_index, note->title, -1, SQLITE_TRANSIENT);

    param_index = sqlite3_bind_parameter_index(stmt, ":content");
    if (param_index == -1)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_bind_text(stmt, param_index, note->content, -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf(RED "[ERR] SQLite: %s" RESET "\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    sqlite3_finalize(stmt);
}
