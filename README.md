# 🗒️ C-Notes (`cn`)

**C-Notes** (`cn`) is a minimalist note-taking command-line application written in C, backed by SQLite. Notes are stored locally in `~/.notes.db`, and the interface is dead simple: just the terminal, no fluff.

---

## 📦 Features

- Create, list, delete, and query notes
- Stores notes in a local SQLite database (`~/.notes.db`)
- Soft deletion (notes aren't lost unless you purge them)
- ANSI-colored output for easier readability
- Written in pure C for performance and portability

---

## 🚀 Usage

Compile it:

```bash
mkdir build
cmake ..
make
````

Run it:

```bash
./cn "Note title" "Note content"      # Create a new note
./cn                                  # List all non-deleted notes
./cn -l                               # Same as above
./cn -a                               # List all notes including deleted
./cn -q <id>                          # Query note by ID
./cn -d <id>                          # Soft-delete note by ID
```

Example:

```bash
$ ./cn "Buy milk" "Don't forget almond milk"
$ ./cn
[1] - Buy milk
    Don't forget almond milk

$ ./cn -d 1
$ ./cn -a
[1] - Buy milk
    Don't forget almond milk
```

---

## 💾 Storage

Notes are stored in a local SQLite database at:

```
~/.notes.db
```

Each note contains:

* `Id` (auto-increment)
* `Title`
* `Content`
* `Deleted` (boolean flag)

No network, no cloud. Your notes, your machine.

---

## 🛠️ Dependencies

* [SQLite3](https://sqlite.org/)
* ANSI terminal (for colored output)

Install SQLite on most distros:

```bash
# Debian/Ubuntu
sudo apt install libsqlite3-dev

# Arch
sudo pacman -S sqlite

# Gentoo
emerge -av sqlite
```

---

## 📁 Project Structure

```text
.
├── main.c         # CLI entry point
├── notes.c        # Database operations
├── notes.h        # Note struct + function declarations
├── CMakeLists.txt # Build configurations for cmake
└── README.md      # You're reading this
```

## 🧠 Author

Daniel Baralt
Built with ❤️, C, and a terminal.
