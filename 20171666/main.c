#include "main.h"

void listCommand(char command[]){
    int temp;
    char name[MAX_NAME_LENGTH];

    if(!strcmp(command, "list_push_back")){
        listPush(0);
    }
    else if(!strcmp(command, "list_push_front")){
        listPush(1);
    }
    else if(!strcmp(command, "list_front")){
        listFrontBack(0);
    }
    else if(!strcmp(command, "list_back")){
        listFrontBack(1);
    }
    else if(!strcmp(command, "list_pop_back")){
        listPop(0);
    }
    else if(!strcmp(command, "list_pop_front")){
        listPop(1);
    }
    else if(!strcmp(command, "list_insert")){
        struct list* list;
        struct list_elem* e;
        struct list_elem* new=(struct list_elem*)malloc(sizeof(struct list_elem));
        struct list_item* item;
        int position, value;

        scanf("%s", name);
        scanf("%d %d",&position, &value);
        list=findList(name);

        if(list==NULL) return;

        e=list_begin(list);
        for(int i=0;i<position && e!=list_end(list);i++)
          e=list_next(e);

        list_insert(e, new);
        item=list_entry(new, struct list_item, elem);
        item->data=value;
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

struct list* findList(char name[50]){
    for(int i=0;i<10;i++){
        if(!strcmp(testList[i].name, name)) 
          return testList[i].start;
    }

    return NULL;
}

void listPush(int idx){
    struct list* list;
    struct list_elem* e=(struct list_elem*)malloc(sizeof(struct list_elem));
    struct list_item* item;
    char name[MAX_NAME_LENGTH];
    int temp;

    scanf("%s %d",name, &temp);
    list=findList(name);

    if(list==NULL) return;

    if(idx==0)
      list_push_back(list, e);
    else
      list_push_front(list, e);

    item=list_entry(e, struct list_item, elem);
    item->data=temp;
}

void listFrontBack(int idx){
    struct list* list;
    struct list_elem* e;
    struct list_item* item;
    char name[MAX_NAME_LENGTH];

    scanf("%s",name);
    list=findList(name);

    if(list!=NULL){
        if(idx==0)
          e=list_front(list);
        else
          e=list_back(list);
    }
    else return;
        
    item=list_entry(e, struct list_item, elem);
    printf("%d\n",item->data);
}

void listPop(int idx){
    struct list* list;
    struct list_elem* e;
    char name[MAX_NAME_LENGTH];

    scanf("%s",name);
    list=findList(name);

    if(list!=NULL){
        if(idx==0)
          e=list_pop_back(list);
        else
          e=list_pop_front(list);
    }
    else return;
}

int main(){
    int i,j;
    char command[MAX_COMMAND_LENGTH];
    char commandCopy[MAX_COMMAND_LENGTH];
    char kind[MAX_KIND_LENGTH];
    char name[MAX_NAME_LENGTH];
    char* commandKind;
    
    while(1){
        scanf("%s",command);
        strcpy(commandCopy, command);

        commandKind=strtok(commandCopy, "_");

        if(!strcmp(command, "quit")) return 0;

        if(!strcmp(command, "create")){
            scanf("%s",kind);

            if(!strcmp(kind, "list")){
                scanf("%s",name);
                for(i=0;i<10;i++){
                    if(testList[i].start==NULL){
                        strcpy(testList[i].name, name);
                        testList[i].start=(struct list*)malloc(sizeof(struct list));
                        list_init(testList[i].start);
                        break;
                    }
                }
                        
            }
            //============ create list =======

            else if(!strcmp(kind, "hash")){
            }
            //============ create hash =======

            else if(!strcmp(kind, "bitmap")){
            }
            //============ create bitmap =====
        }
        else if(!strcmp(command, "dumpdata")){
            struct list* list;
            struct hash* hash;
            struct bitmap* bitmap;

            scanf("%s",name);

            list=findList(name);
           // hash=findHash(name);
            //bitmap=findBitmap(name);
            if(list!=NULL){
                struct list_elem* begin=list_begin(list);
                struct list_elem* end=list_end(list);
                struct list_item* item;
                
                for(struct list_elem* e=begin; e!=end; e=list_next(e)){
                    item=list_entry(e, struct list_item, elem);
                    printf("%d ",item->data);
                }
                printf("\n");
            }
            else if(hash!=NULL){
            }
            else if(bitmap!=NULL){
            }
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
