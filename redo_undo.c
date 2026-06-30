#include "redo_undo.h"
#include "text_ops.h"


void initializeStack(DynamicArrayStack *stack)
{
    stack->actions = (Action *)malloc(INITIAL_STACK_CAPACITY * sizeof(Action));

    if (stack->actions == NULL)
    {
        printf("Stack memory allocation failed.\n");
        exit(1);
    }

    stack->size = 0;
    stack->capacity = INITIAL_STACK_CAPACITY;
}


/* =========================================
   Check Stack Empty
   ========================================= */

int isStackEmpty(DynamicArrayStack *stack)
{
    return (stack->size == 0);
}


/* =========================================
   Push Action
   ========================================= */

void pushAction(DynamicArrayStack *stack, Action action)
{
    /* Resize if stack full */
    if (stack->size == stack->capacity)
    {
        stack->capacity *= 2;

        stack->actions = realloc(stack->actions, stack->capacity * sizeof(Action));

        if (stack->actions == NULL)
        {
            printf("Stack reallocation failed.\n");
            exit(1);
        }
    }

    stack->actions[stack->size] = action;

    stack->size++;
}


/* =========================================
   Pop Action
   ========================================= */

Action popAction(DynamicArrayStack *stack)
{
    Action emptyAction;

    strcpy(emptyAction.operation, "");

    if (isStackEmpty(stack))
    {
        printf("Stack is empty.\n");
        return emptyAction;
    }

    stack->size--;

    return stack->actions[stack->size];
}


/* =========================================
   Free Stack
   ========================================= */

void freeStack(DynamicArrayStack *stack)
{
    free(stack->actions);

    stack->size = 0;
    stack->capacity = 0;
}


static void goToLine(TextEditor *editor, int lineNum) {
    if (editor->head == NULL) return;
    editor->cursor = editor->head;
    editor->cursorLine = 1;
    while (editor->cursor != NULL && editor->cursorLine < lineNum) {
        editor->cursor = editor->cursor->next;
        editor->cursorLine++;
    }
}

static void restoreLine(TextEditor *editor, int linenum, const char *text) {
    Node *newNode = createLine(text);
    if (!newNode) return;
    
    if (editor->head == NULL) {
        editor->head = editor->tail = editor->cursor = newNode;
        editor->cursorLine = 1;
    } else if (linenum == 1) {
        newNode->next = editor->head;
        editor->head->prev = newNode;
        editor->head = newNode;
    } else {
        Node *curr = editor->head;
        int currLine = 1;
        while (curr->next != NULL && currLine < linenum - 1) {
            curr = curr->next;
            currLine++;
        }
        newNode->next = curr->next;
        newNode->prev = curr;
        if (curr->next) curr->next->prev = newNode;
        else editor->tail = newNode;
        curr->next = newNode;
    }
    editor->cursor = newNode;
    editor->cursorLine = linenum;
}

/* =========================================
   Undo Operation
   ========================================= */

void undo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{
    if (isStackEmpty(undoStack))
    {
        printf("Nothing to undo.\n");
        return;
    }

    Action action = popAction(undoStack);

    editor->isUndoRedo = 1;

    if (strcmp(action.operation, "insert") == 0)
    {
        goToLine(editor, action.cursorLine);
        editor->cursorPos = action.cursorPos;
        deleteCharacters(editor, strlen(action.text));
    }
    else if (strcmp(action.operation, "delete") == 0)
    {
        goToLine(editor, action.cursorLine);
        editor->cursorPos = action.cursorPos;
        insertText(editor, action.text);
    }
    else if (strcmp(action.operation, "newline") == 0)
    {
        deleteLine(editor, action.cursorLine);
    }
    else if (strcmp(action.operation, "deleteLine") == 0)
    {
        restoreLine(editor, action.cursorLine, action.text);
    }

    editor->isUndoRedo = 0;

    pushAction(redoStack, action);
    printf("Undo successful.\n");
}


/* =========================================
   Redo Operation
   ========================================= */

void redo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{
    if (isStackEmpty(redoStack))
    {
        printf("Nothing to redo.\n");
        return;
    }

    Action action = popAction(redoStack);

    editor->isUndoRedo = 1;

    if (strcmp(action.operation, "insert") == 0)
    {
        goToLine(editor, action.cursorLine);
        editor->cursorPos = action.cursorPos;
        insertText(editor, action.text);
    }
    else if (strcmp(action.operation, "delete") == 0)
    {
        goToLine(editor, action.cursorLine);
        editor->cursorPos = action.cursorPos;
        deleteCharacters(editor, strlen(action.text));
    }
    else if (strcmp(action.operation, "newline") == 0)
    {
        goToLine(editor, action.cursorLine - 1);
        insertNewLine(editor);
    }
    else if (strcmp(action.operation, "deleteLine") == 0)
    {
        deleteLine(editor, action.cursorLine);
    }

    editor->isUndoRedo = 0;

    pushAction(undoStack, action);
    printf("Redo successful.\n");
}