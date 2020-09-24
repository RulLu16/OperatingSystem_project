#include "main.h"

int main(){
    char command[MAX_COMMAND_LENGTH];
    char structKind[MAX_KIND_LENGTH];
    char structName[MAX_NAME_LENGTH];
    
    while(1){
        scanf("%s",command);

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
        else if(!strcmp(command, "list_push_back")){
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
}
