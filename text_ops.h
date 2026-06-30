/* =========================================
   text_ops.h
   ========================================= */

#ifndef TEXT_OPS_H
#define TEXT_OPS_H

#include "text_editor.h"


/* ---------- Text Operations ---------- */

void insertText(TextEditor *editor, const char *text);

void insertNewLine(TextEditor *editor);

int deleteCharacters(TextEditor *editor, int numChars);

void deleteLine(TextEditor *editor, int linenum);


/* ---------- Clipboard Operations ---------- */

void copyText(TextEditor *editor, int start, int end);

void cutText(TextEditor *editor, int start, int end);

void pasteText(TextEditor *editor);

#endif
