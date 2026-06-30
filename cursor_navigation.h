#ifndef CURSOR_NAVIGATION_H
#define CURSOR_NAVIGATION_H

#include "text_editor.h"

/* =========================
   VERTICAL NAVIGATION
   ========================= */

// Move cursor one line up
void moveCursorUp(TextEditor *editor);

// Move cursor one line down
void moveCursorDown(TextEditor *editor);


/* =========================
   HORIZONTAL NAVIGATION
   ========================= */

// Move cursor one character left
void moveCursorLeft(TextEditor *editor);

// Move cursor one character right
void moveCursorRight(TextEditor *editor);


/* =========================
   FILE BOUNDARIES
   ========================= */

// Jump to first line of file
void jumpToStartOfFile(TextEditor *editor);

// Jump to last line of file
void jumpToEndOfFile(TextEditor *editor);


/* =========================
   LINE BOUNDARIES
   ========================= */

// Move cursor to start of current line
void jumpToStartOfLine(TextEditor *editor);

// Move cursor to end of current line
void jumpToEndOfLine(TextEditor *editor);

#endif