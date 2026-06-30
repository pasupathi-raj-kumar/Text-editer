#include <stdio.h>
#include <string.h>
#include "cursor_navigation.h"
#include "display_search.h"
#include "text_editor.h"
#include "text_ops.h"
#include "file_ops.h"
#include "redo_undo.h"

int main() {

    char choice[2048];
    char *cmd;

    // Create editor + stacks
   TextEditor editor;
   initializeEditor(&editor);
   printf("Welcome to the Text Editor!\n");
   printf("Do you want to open an existing file? (y/n): ");
   char response;
   scanf("%c", &response);
   getchar(); // Consume newline character left in buffer
   if (response == 'y' || response == 'Y') 
   {
        printf("Enter the file to open: ");
        char filename[100];
        scanf(" %99s", filename);
        loadFile(&editor, filename);
   }

    


    printf("===== TEXT EDITOR STARTED =====\n");

    while (1) {

        printf("\nText Editor Commands:\n");
        printf("1. insert <text>   -> insert text at cursor\n");
        printf("2. insert           -> create new line\n");
        printf("3. delete\n");
        printf("4. undo\n");
        printf("5. redo\n");
        printf("6. navigations\n");
        printf("7. print\n");
        printf("8. save\n");
        printf("9. exit\n");
      

        printf("\nEnter command: ");

        // IMPORTANT: clear buffer issue fix
        
        scanf(" %2047[^\n]", choice);

        cmd = strtok(choice, " ");

       /* ================= 1. INSERT ================= */
   
        if (cmd != NULL && (strcmp(cmd, "insert") == 0 || strcmp(cmd, "1") == 0 || strcmp(cmd, "2") == 0))
        {
            char *text = strtok(NULL, "");

            if (strcmp(cmd, "2") == 0 || (strcmp(cmd, "insert") == 0 && text == NULL))
            {
                insertNewLine(&editor);
                printf("[OK] New line inserted successfully.\n");
            }
            else
            {
                if (text == NULL) {
                    printf("[ERROR] Missing text for insert command.\n");
                } else {
                    insertText(&editor, text);
                    printf("[OK] Text inserted successfully.\n");
                }
            }
        }
        /* =================2. DELETE ================= */
        else if (cmd != NULL && (strcmp(cmd, "delete") == 0 || strcmp(cmd, "3") == 0)) {

           printf("Want to delete characters or line? (c/l): ");
           char delChoice;
           scanf(" %c", &delChoice);
            if (delChoice == 'l' || delChoice == 'L')
            {
                printf("Enter the line number you want to delete: ");
                int lineNum = -1;
                scanf("%d", &lineNum);
            
                deleteLine(&editor, lineNum);
                printf("[OK] Line deleted successfully.\n");
                continue;
            }
            else if (delChoice == 'c' || delChoice == 'C')
            {
                printf("Enter number of characters to delete: ");
               int n = -1;
                scanf("%d", &n);
                if(deleteCharacters(&editor, n))
                {
                printf("[OK] Deleted %d characters successfully.\n", n);  
                }
            }
            else
            {
                printf("[ERROR] Invalid delete choice\n");
                continue;
            }

            
        }

        /* ================= 3. UNDO ================= */
        else if (cmd != NULL && (strcmp(cmd, "undo") == 0 || strcmp(cmd, "4") == 0))
        {
            undo(&editor, &editor.undoStack, &editor.redoStack);
        }

        /* ================= 4. REDO ================= */
        else if (cmd != NULL && (strcmp(cmd, "redo") == 0 || strcmp(cmd, "5") == 0)) {

            redo(&editor, &editor.undoStack, &editor.redoStack);
        }

         /* ================= 5. Navigations ================= */
        else if (cmd != NULL && (strcmp(cmd, "navigations") == 0 || strcmp(cmd, "6") == 0)) {
                printf("Navigation Commands:\n");
                printf("1. up\n");
                printf("2. down\n");    
                printf("3. left\n");
                printf("4. right\n");
                printf("5. start_file\n");
                printf("6. end_file\n");    
                printf("7. start_line\n");
                printf("8. end_line\n");
                printf("\nEnter the option :  ");
                int option = -1;
                scanf("%d", &option);
                if (option == 1) {
                    moveCursorUp(&editor);
                } else if (option == 2) {
                    moveCursorDown(&editor);
                } else if (option == 3) {
                    moveCursorLeft(&editor);
                } else if (option == 4) {
                    moveCursorRight(&editor);
                } else if (option == 5) {
                    jumpToStartOfFile(&editor);
                } else if (option == 6) {
                    jumpToEndOfFile(&editor);
                } else if (option == 7) {
                    jumpToStartOfLine(&editor);
                } else if (option == 8) {
                    jumpToEndOfLine(&editor);
                } else {
                    printf("[ERROR] Invalid navigation command\n");
                }
        }

        /* ================= 6. PRINT ================= */
        else if (cmd != NULL && (strcmp(cmd, "print") == 0 || strcmp(cmd, "7") == 0)) {

           displayText(&editor);
        }

         /* ================= 7. SAVE ================= */
        else if (cmd != NULL && (strcmp(cmd, "save") == 0 || strcmp(cmd, "8") == 0)) {

            printf("Enter filename to save: ");
            char filename[100];
            scanf(" %99s", filename);  
            saveFile(&editor, filename);

        }

        /* ================= 8. EXIT ================= */
        else if (cmd != NULL && (strcmp(cmd, "exit") == 0 || strcmp(cmd, "9") == 0)) {

            printf("[EXIT] Exiting Text Editor...\n");
            freeEditor(&editor);
            break;
        }



        /* ================= INVALID ================= */
        else {
            printf("[ERROR] Invalid command\n");
        }

    }
    

    return 0;
}