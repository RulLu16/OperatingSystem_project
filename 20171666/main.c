#include "main.h"

void listCommand(char command[]){

    if(!strcmp(command, "list_push_back")){
    }
    else if(!strcmp(command, "list_push_front")){
    }
    else if(!strcmp(command, "list_front")){
    }
    else if(!strcmp(command, "list_back")){
    }
    else if(!strcmp(command, "list_pop_back")){
    }
    else if(!strcmp(command, "list_pop_front")){
    }
    else if(!strcmp(command, "list_insert")){
    }
    else if(!strcmp(command, "list_insert_ordered")){
    }
    else if(!strcmp(command, "list_empty")){
    }
    else if(!strcmp(command, "list_size")){
    }
    else if(!strcmp(command, "list_max")){
    }
    else if(!strcmp(command, "list_min")){
    }
    else if(!strcmp(command, "list_remove")){
    }
    else if(!strcmp(command, "list_reverse")){
    }
    else if(!strcmp(command, "list_shuffle")){
    }
    else if(!strcmp(command, "list_sort")){
    }
    else if(!strcmp(command, "list_splice")){
    }
    else if(!strcmp(command, "list_swap")){
    }
    else if(!strcmp(command, "list_unique")){
    }
}

void hashCommand(char command[]){
    
    if(!strcmp(command, "hash_insert")){
    }
    else if(!strcmp(command, "hash_apply")){
    }
    else if(!strcmp(command, "hash_delete")){
    }
    else if(!strcmp(command, "hash_empty")){
    }
    else if(!strcmp(command, "hash_size")){
    }
    else if(!strcmp(command, "hash_clear")){
    }
    else if(!strcmp(command, "hash_find")){
    }
    else if(!strcmp(command, "hash_replace")){
    }
}

void bitmapCommand(char command[]){

    if(!strcmp(command, "bitmap_mark")){
    }
    else if(!strcmp(command, "bitmap_all")){
    }
    else if(!strcmp(command, "bitmap_any")){
    }
    else if(!strcmp(command, "bitmap_contains")){
    }
    else if(!strcmp(command, "bitmap_count")){
    }
    else if(!strcmp(command, "bitmap_dump")){
    }
    else if(!strcmp(command, "bitmap_expand")){
    }
    else if(!strcmp(command, "bitmap_flip")){
    }
    else if(!strcmp(command, "bitmap_none")){
    }
    else if(!strcmp(command, "bitmap_reset")){
    }
    else if(!strcmp(command, "bitmap_scan")){
    }
    else if(!strcmp(command, "bitmap_scan_and_flip")){
    }
    else if(!strcmp(command, "bitmap_set")){
    }
    else if(!strcmp(command, "bitmap_set_all")){
    }
    else if(!strcmp(command, "bitmap_set_multiple")){
    }
    else if(!strcmp(command, "bitmap_size")){
    }
    else if(!strcmp(command, "bitmap_test")){
    }
}

int main(){
    char command[MAX_COMMAND_LENGTH];
    char commandCopy[MAX_COMMAND_LENGTH];
    char structKind[MAX_KIND_LENGTH];
    char structName[MAX_NAME_LENGTH];
    char* commandKind;
    
    while(1){
        scanf("%s",command);
        strcpy(commandCopy, command);

        commandKind=strtok(commandCopy, "_");

        if(!strcmp(command, "quit")) return 0;

        if(!strcmp(command, "create")){
            scanf("%s",structKind);

            if(!strcmp(structKind, "list")){
            }
            //============ create list =======

            else if(!strcmp(struckKind, "hash")){
            }
            //============ create hash =======

            else if(!strcmp(struckKind, "bitmap")){
            }
            //============ create bitmap =====
        }
        else if(!strcmp(command, "dumpdata")){
        }
        else if(!strcmp(command, "delete")){
        }

        //====== list command start ========
        else if(!strcmp(commandKind, "list")){
            listCommand(command);
        }
        else if(!strcmp(commandKind, "hash")){
            hashCommand(command);
        }
        else if(!strcmp(commandKind, "bitmap")){
            bitmapCommand(command);
        }
    }
}
