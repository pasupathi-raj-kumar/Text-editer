#ifndef REDO_UNDO_H
#define REDO_UNDO_H

#include "text_editor.h"


void initializeStack(DynamicArrayStack *stack);

void pushAction(DynamicArrayStack *stack, Action action);

Action popAction(DynamicArrayStack *stack);

int isStackEmpty(DynamicArrayStack *stack);

void freeStack(DynamicArrayStack *stack);

void undo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);

void redo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);


#endif