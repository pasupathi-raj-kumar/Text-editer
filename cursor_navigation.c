/* =========================================
   cursor_navigation.c
   ========================================= */

#include "text_editor.h"


/* =========================================
   Move Cursor Left
   ========================================= */

void moveCursorLeft(TextEditor *editor)
{
    if (editor->cursor == NULL)
    {
        return;
    }

    if (editor->cursorPos > 0)
    {
        editor->cursorPos--;
    }
    else
    {
        printf("Already at start of line.\n");
    }
}


/* =========================================
   Move Cursor Right
   ========================================= */

void moveCursorRight(TextEditor *editor)
{
    if (editor->cursor == NULL)
    {
        return;
    }

    int lineLength = strlen(editor->cursor->line);

    if (editor->cursorPos < lineLength)
    {
        editor->cursorPos++;
    }
    else
    {
        printf("Already at end of line.\n");
    }
}


/* =========================================
   Move Cursor Up
   ========================================= */

void moveCursorUp(TextEditor *editor)
{
    if (editor->cursor == NULL)
    {
        return;
    }

    if (editor->cursor->prev != NULL)
    {
        editor->cursor = editor->cursor->prev;

        editor->cursorLine--;

        int lineLength =
            strlen(editor->cursor->line);

        if (editor->cursorPos > lineLength)
        {
            editor->cursorPos = lineLength;
        }
    }
    else
    {
        printf("Already at first line.\n");
    }
}


/* =========================================
   Move Cursor Down
   ========================================= */

void moveCursorDown(TextEditor *editor)
{
    if (editor->cursor == NULL)
    {
        return;
    }

    if (editor->cursor->next != NULL)
    {
        editor->cursor = editor->cursor->next;

        editor->cursorLine++;

        int lineLength =
            strlen(editor->cursor->line);

        if (editor->cursorPos > lineLength)
        {
            editor->cursorPos = lineLength;
        }
    }
    else
    {
        printf("Already at last line.\n");
    }
}


/* =========================================
   Jump To Start Of Line
   ========================================= */

void jumpToStartOfLine(TextEditor *editor)
{
    if (editor->cursor == NULL)
    {
        return;
    }

    editor->cursorPos = 0;
}


/* =========================================
   Jump To End Of Line
   ========================================= */

void jumpToEndOfLine(TextEditor *editor)
{
    if (editor->cursor == NULL)
    {
        return;
    }

    editor->cursorPos = strlen(editor->cursor->line);
}

// Jump to first line of file
void jumpToStartOfFile(TextEditor *editor)
{
    if (editor->head == NULL)
    {
        return;
    }

    editor->cursor = editor->head;
    editor->cursorLine = 1;

    int lineLength =
        strlen(editor->cursor->line);

    if (editor->cursorPos > lineLength)
    {
        editor->cursorPos = lineLength;
    }
}

// Jump to last line of file
void jumpToEndOfFile(TextEditor *editor)
{
    if (editor->tail == NULL)
    {
        return;
    }

    editor->cursor = editor->tail;
    
    int count = 0;
    Node *curr = editor->head;
    while(curr != NULL) {
        count++;
        curr = curr->next;
    }
    editor->cursorLine = count;

    int lineLength =
        strlen(editor->cursor->line);

    if (editor->cursorPos > lineLength)
    {
        editor->cursorPos = lineLength;
    }
}
