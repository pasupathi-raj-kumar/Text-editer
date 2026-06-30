/* =========================================
   text_editor.h
   ========================================= */

#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define INITIAL_STACK_CAPACITY 10


/* ---------- Node Structure ---------- */

typedef struct Node
{
    char line[MAX_LINE_LENGTH];

    struct Node *prev;
    struct Node *next;

} Node;


/* ---------- Undo / Redo Action ---------- */

typedef struct
{
    char operation[20];

    char text[MAX_LINE_LENGTH];

    int cursorLine;
    int cursorPos;

} Action;


/* ---------- Dynamic Stack ---------- */

typedef struct
{
    Action *actions;

    int size;
    int capacity;

} DynamicArrayStack;


/* ---------- Main Text Editor ---------- */

typedef struct
{
    Node *head;
    Node *tail;

    Node *cursor;

    int cursorLine;
    int cursorPos;

    DynamicArrayStack undoStack;
    DynamicArrayStack redoStack;

    char clipboard[MAX_LINE_LENGTH];
    int isUndoRedo;

} TextEditor;

// Function Prototypes
// Editor Initialization and Memory Management
void initializeEditor(TextEditor *editor);


void freeEditor(TextEditor *editor);

// Line Operations 
Node *createLine(const char *text);

// Append line at end (used for loading files)
void appendLine(TextEditor *editor, const char *text);


#endif