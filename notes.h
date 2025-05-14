//
// Created by dbaralt on 5/12/25.
//

#ifndef NOTES_H
#define NOTES_H

#define RESET       "\033[0m"
#define RED         "\033[1;31m"
#define GREEN       "\033[1;32m"
#define YELLOW      "\033[1;33m"

#include <sqlite3.h>

typedef struct
{
    long id;
    char title[50];
    char content[500];
} Note;

sqlite3* load_notes(const char* database);
void list_notes(sqlite3* db);
void list_all_notes(sqlite3* db);
void delete_note(sqlite3* db, long id);
void get_note(sqlite3* db, long id);
void create_note(sqlite3* db, const Note* note);

#endif //NOTES_H
