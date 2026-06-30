#ifndef DISPLAY_SEARCH_H
#define DISPLAY_SEARCH_H

#include "text_editor.h"

/* =========================
   DISPLAY FUNCTIONS
   ========================= */

// Render the full text editor content
void displayText(TextEditor *editor);

// Show current cursor position (line, column)
void showCursorPosition(TextEditor *editor);


/* =========================
   SEARCH FUNCTIONS
   ========================= */

// Find all occurrences of a pattern in the text
void findText(TextEditor *editor, const char *pattern);


/* =========================
   REPLACE FUNCTIONS
   ========================= */

// Replace first/all occurrences of a pattern with new text
void replaceText(TextEditor *editor, const char *oldText, const char *newText);

#endif