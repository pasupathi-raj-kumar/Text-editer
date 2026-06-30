#include "file_ops.h"
#include "display_search.h"

/* =========================================
   Load File
   ========================================= */

void loadFile(TextEditor *editor, const char *filename)
{
    FILE *fp = fopen(filename, "r");

 

    if (fp == NULL)
    {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\n")] = '\0';
        appendLine(editor, line);
    }

    fclose(fp);

    /* Reset cursor to the beginning of the file */
    if (editor->head != NULL) {
        editor->cursor = editor->head;
        editor->cursorLine = 1;
        editor->cursorPos = 0;
    }

    printf("File loaded successfully.\n");

}


/* =========================================
   Save File
   ========================================= */

void saveFile(TextEditor *editor, const char *filename)
{
    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("Error: Cannot save file %s\n", filename);
        return;
    }

    Node *current = editor->head;

    while (current != NULL)
    {
        fprintf(fp, "%s\n", current->line);

        current = current->next;
    }

    fclose(fp);

    printf("File saved successfully.\n");
}


/* =========================================
   Close File / Clear Editor
   ========================================= */

void closeFile(TextEditor *editor)
{
    Node *temp;
    Node *current = editor->head;

    while (current != NULL)
    {
        temp = current;

        current = current->next;

        free(temp);
    }

    editor->head = NULL;
    editor->tail = NULL;
    editor->cursor = NULL;

    editor->cursorLine = 0;
    editor->cursorPos = 0;

    printf("Editor cleared successfully.\n");
}