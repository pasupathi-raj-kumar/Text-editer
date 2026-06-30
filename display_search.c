#include "text_editor.h"

void displayText(TextEditor *editor)
{
    if (editor->head == NULL)
    {
        printf("Editor is empty.\n");
        return;
    }

    Node *current = editor->head;

    int lineNumber = 1;

    printf("\n========== TEXT EDITOR ==========\n");

    while (current != NULL)
    {
        printf("Line %d: %s\n",
               lineNumber,
               current->line);

        current = current->next;

        lineNumber++;
    }

    printf("\nCursor Position -> Line: %d | Column: %d\n",
           editor->cursorLine,
           editor->cursorPos);

    printf("=================================\n");
}


/* =========================================
   Show Cursor Position
   ========================================= */

void showCursorPosition(TextEditor *editor)
{
    printf("Cursor Position -> Line: %d | Column: %d\n",
           editor->cursorLine,
           editor->cursorPos);
}


/* =========================================
   Find Text
   ========================================= */

void findText(TextEditor *editor, const char *word)
{
    if (editor->head == NULL)
    {
        printf("Editor is empty.\n");
        return;
    }

    Node *current = editor->head;

    int lineNumber = 1;

    int found = 0;

    while (current != NULL)
    {
        char *position = strstr(current->line, word);

        if (position != NULL)
        {
            int column =
                position - current->line;

            printf("Found at Line %d, Column %d\n",
                   lineNumber,
                   column);

            found = 1;
        }

        current = current->next;

        lineNumber++;
    }

    if (!found)
    {
        printf("Text not found.\n");
    }
}


/* =========================================
   Replace Text
   ========================================= */

void replaceText(TextEditor *editor,
                 const char *oldWord,
                 const char *newWord)
{
    if (editor->head == NULL)
    {
        printf("Editor is empty.\n");
        return;
    }

    Node *current = editor->head;

    int replaced = 0;

    while (current != NULL)
    {
        char buffer[MAX_LINE_LENGTH];

        char *position =
            strstr(current->line, oldWord);

        if (position != NULL)
        {
            int index =
                position - current->line;

            /* Copy first part */
            strncpy(buffer,
                    current->line,
                    index);

            buffer[index] = '\0';

            /* Add new word */
            strcat(buffer, newWord);

            /* Add remaining part */
            strcat(buffer,
                   position + strlen(oldWord));

            strcpy(current->line, buffer);

            replaced++;
        }

        current = current->next;
    }

    printf("%d occurrence(s) replaced.\n",
           replaced);
}

