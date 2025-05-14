#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notes.h"

int main(int argc, char** argv)
{
    const char* home_dir = getenv("HOME");
    char db_path[512];
    snprintf(db_path, sizeof(db_path), "%s/.notes.db", home_dir);
    sqlite3* db = load_notes(db_path);

    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-l") == 0)) {
        list_notes(db);
    }
    else if (argc == 2 && strcmp(argv[1], "-a") == 0) {
        list_all_notes(db);
    }
    else if (argc == 3 && strcmp(argv[1], "-d") == 0) {
        const long id = strtol(argv[2], NULL, 10);
        delete_note(db, id);
    }
    else if (argc == 3 && strcmp(argv[1], "-q") == 0) {
        const long id = strtol(argv[2], NULL, 10);
        get_note(db, id);
    }
    else if (argc == 3 && argv[1][0] != '-') {
        Note new_note;
        strncpy(new_note.title, argv[1], sizeof(new_note.title) - 1);
        new_note.title[sizeof(new_note.title) - 1] = '\0';

        strncpy(new_note.content, argv[2], sizeof(new_note.content) - 1);
        new_note.content[sizeof(new_note.content) - 1] = '\0';

        create_note(db, &new_note);
    }
    else {
        printf(RED "Invalid usage.\n" RESET);
        printf("Usage:\n");
        printf("  %s                 List notes\n", argv[0]);
        printf("  %s -l              List notes (default)\n", argv[0]);
        printf("  %s -a              List all notes\n", argv[0]);
        printf("  %s -d <id>         Delete note by ID\n", argv[0]);
        printf("  %s -q <id>         Query note by ID\n", argv[0]);
        printf("  %s \"title\" \"content\"   Create a new note\n", argv[0]);
    }

    sqlite3_close(db);
    return 0;
}
