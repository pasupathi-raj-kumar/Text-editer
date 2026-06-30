//insert, delete copy, paste
#include "text_ops.h"
#include "redo_undo.h"
// Insert text at cursor position in current line
void insertText(TextEditor *editor, const char *text)
{
    if (editor->cursor == NULL)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));

        if (newNode == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }

        newNode->line[0] = '\0';
        newNode->prev = NULL;
        newNode->next = NULL;

        editor->head = newNode;
        editor->tail = newNode;
        editor->cursor = newNode;

        editor->cursorLine = 1;
        editor->cursorPos = 0;
    }

    Node *current = editor->cursor;

    int currLen = strlen(current->line);
    int textLen = strlen(text);

    /* 🚨 SAFETY CHECK */
    if (currLen + textLen >= MAX_LINE_LENGTH)
    {
        printf("Line overflow prevented!\n");
        return;
    }

    /* clamp cursor just in case */
    if (editor->cursorPos > currLen)
        editor->cursorPos = currLen;

    char temp[MAX_LINE_LENGTH];

    /* safe copy of right part */
    strncpy(temp,
            current->line + editor->cursorPos,
            MAX_LINE_LENGTH - 1);
    temp[MAX_LINE_LENGTH - 1] = '\0';

    /* build final string safely */
    current->line[editor->cursorPos] = '\0';

    strncat(current->line, text,
            MAX_LINE_LENGTH - strlen(current->line) - 1);

    strncat(current->line, temp,
            MAX_LINE_LENGTH - strlen(current->line) - 1);

    editor->cursorPos += textLen;

    /* undo stack */
    Action action;
    strcpy(action.operation, "insert");
    strcpy(action.text, text);
    action.cursorLine = editor->cursorLine;
    action.cursorPos = editor->cursorPos - textLen;

    if (!editor->isUndoRedo) {
        pushAction(&editor->undoStack, action);
        editor->redoStack.size = 0;
    }
}

void insertNewLine(TextEditor *editor)
{
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    strcpy(newNode->line, "");
    newNode->next = NULL;
    newNode->prev = NULL;

    /* Empty editor */
    if (editor->head == NULL)
    {
        editor->head = newNode;
        editor->tail = newNode;
        editor->cursor = newNode;

        editor->cursorLine = 1;
        editor->cursorPos = 0;
    }
    else
    {
        Node *curr = editor->cursor;

        /* Insert after current line */
        newNode->next = curr->next;
        newNode->prev = curr;

        if (curr->next != NULL)
        {
            curr->next->prev = newNode;
        }
        else
        {
            editor->tail = newNode;
        }

        curr->next = newNode;

        editor->cursor = newNode;
        editor->cursorLine++;
        editor->cursorPos = 0;
    }

    /* Store in undo stack if required */
    Action action;
    strcpy(action.operation, "newline");
    strcpy(action.text, "");
    action.cursorLine = editor->cursorLine;
    action.cursorPos = 0;

    if (!editor->isUndoRedo) {
        pushAction(&editor->undoStack, action);
        editor->redoStack.size = 0;
    }

}


int deleteCharacters(TextEditor *editor, int numChars)
{
    /* Check if cursor exists */
    if (editor->cursor == NULL)
    {
        printf("No text available.\n");
        return 0;
    }

    Node *current = editor->cursor;

    int lineLength = strlen(current->line);

    /* Check valid deletion */
    if (editor->cursorPos + numChars > lineLength)
    {
        printf("Cannot delete %d characters.\n", numChars);
        return 0;
    }

    /* Store deleted text */
    char deletedText[MAX_LINE_LENGTH];

    strncpy(deletedText,
            current->line + editor->cursorPos,
            numChars);

    deletedText[numChars] = '\0';


    /* Shift remaining characters left */
    memmove(current->line + editor->cursorPos,
            current->line + editor->cursorPos + numChars,
            lineLength - editor->cursorPos - numChars + 1);

    printf("%d characters deleted successfully.\n", numChars);
    //push action to undo stack
    Action action;
    strcpy(action.operation, "delete");
    strcpy(action.text, deletedText);
    action.cursorLine = editor->cursorLine;
    action.cursorPos = editor->cursorPos;
    if (!editor->isUndoRedo) {
        pushAction(&editor->undoStack, action);
        editor->redoStack.size = 0;
    }
    return 1;
}


void deleteLine(TextEditor *editor, int linenum)
{
    if (editor->head == NULL)
    {
        printf("Editor is empty.\n");
        return;
    }

    /* Find the line to delete */
    Node *temp = editor->head;
    int currentLine = 1;

    while (temp != NULL && currentLine < linenum)
    {
        temp = temp->next;
        currentLine++;
    }

    /* Invalid line number */
    if (temp == NULL)
    {
        printf("Invalid line number.\n");
        return;
    }

    /* Store action for Undo BEFORE deleting */
    Action action;
    strcpy(action.operation, "deleteLine");
    strcpy(action.text, temp->line);
    action.cursorLine = linenum;
    action.cursorPos = 0;

    if (!editor->isUndoRedo) {
        pushAction(&editor->undoStack, action);
        editor->redoStack.size = 0;
    }

    /* Only one node */
    if (editor->head == editor->tail)
    {
        editor->head = NULL;
        editor->tail = NULL;
        editor->cursor = NULL;
        editor->cursorLine = 0;
        editor->cursorPos = 0;
    }
    /* First node */
    else if (temp == editor->head)
    {
        editor->head = temp->next;
        editor->head->prev = NULL;

        editor->cursor = editor->head;
        editor->cursorLine = 1;
    }
    /* Last node */
    else if (temp == editor->tail)
    {
        editor->tail = temp->prev;
        editor->tail->next = NULL;

        editor->cursor = editor->tail;
        editor->cursorLine = linenum - 1;
    }
    /* Middle node */
    else
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        editor->cursor = temp->next;
        editor->cursorLine = linenum;
    }

    free(temp);

    editor->cursorPos = 0;

    printf("Line %d deleted successfully.\n", linenum);
}

