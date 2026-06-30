

#include "text_editor.h"


/* =========================================
   Initialize Editor
   ========================================= */

void initializeEditor(TextEditor *editor)
{
    editor->head = NULL;
    editor->tail = NULL;
    editor->cursor = NULL;

    editor->cursorLine = 0;
    editor->cursorPos = 0;

    /* Initialize clipboard */
    strcpy(editor->clipboard, "");
    
    editor->isUndoRedo = 0;

    /* ---------- Initialize Undo Stack ---------- */

    editor->undoStack.actions =
        (Action *)malloc(INITIAL_STACK_CAPACITY * sizeof(Action));

    if (editor->undoStack.actions == NULL)
    {
        printf("Undo stack memory allocation failed.\n");
        exit(1);
    }

    editor->undoStack.size = 0;
    editor->undoStack.capacity = INITIAL_STACK_CAPACITY;


    /* ---------- Initialize Redo Stack ---------- */

    editor->redoStack.actions =
        (Action *)malloc(INITIAL_STACK_CAPACITY * sizeof(Action));

    if (editor->redoStack.actions == NULL)
    {
        printf("Redo stack memory allocation failed.\n");
        exit(1);
    }

    editor->redoStack.size = 0;
    editor->redoStack.capacity = INITIAL_STACK_CAPACITY;

    printf("Text Editor Initialized Successfully.\n");
}


Node *createLine(const char *text)
{
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    strcpy(newNode->line, text);

    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

/* =========================================
   Append Line at End
   ========================================= */

void appendLine(TextEditor *editor, const char *text)
{
    Node *newNode = createLine(text);

    if (newNode == NULL)
    {
        return;
    }

    /* If editor empty */
    if (editor->head == NULL)
    {
        editor->head = newNode;
        editor->tail = newNode;
        editor->cursor = newNode;

        editor->cursorLine = 1;
        editor->cursorPos = strlen(text);
    }
    else
    {
        editor->tail->next = newNode;
        newNode->prev = editor->tail;

        editor->tail = newNode;
        editor->cursor = newNode;

        editor->cursorLine++;
        editor->cursorPos = strlen(text);
    }
}


/* =========================================
   Free Editor Memory
   ========================================= */

void freeEditor(TextEditor *editor)
{
    Node *temp;
    Node *current = editor->head;

    /* Free linked list */
    while (current != NULL)
    {
        temp = current;

        current = current->next;

        free(temp);
    }

    /* Free stacks */
    free(editor->undoStack.actions);
    free(editor->redoStack.actions);

    editor->head = NULL;
    editor->tail = NULL;
    editor->cursor = NULL;

    printf("Editor memory released successfully.\n");
}