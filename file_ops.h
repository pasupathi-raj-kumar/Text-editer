/* =========================================
   file_ops.h
   ========================================= */

#ifndef FILE_OPS_H
#define FILE_OPS_H

#include "text_editor.h"


/* ---------- File Operations ---------- */

void loadFile(TextEditor *editor, const char *filename);

void saveFile(TextEditor *editor, const char *filename);

void closeFile(TextEditor *editor);

#endif