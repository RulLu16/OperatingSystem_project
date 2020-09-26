#include "main.h"

void listCommand(char command[]){
    char* name=(char*)malloc(sizeof(char)*MAX_NAME_LENGTH);
    struct list* list;
    struct list_elem* e;
    struct list_item* item;

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
        item=(struct list_item*)malloc(sizeof(struct list_item));
        int position, value;

        scanf("%s", name);
        scanf("%d %d",&position, &value);
        list=findList(name);

        if(list==NULL) return;

        e=list_begin(list);
        item->data=value;
        for(int i=0;i<position;i++)
          e=list_next(e);

        list_insert(e, &(item->elem));
    }
    else if(!strcmp(command, "list_insert_ordered")){
        item=(struct list_item*)malloc(sizeof(struct list_item));
        int value;

        scanf("%s %d", name, &value);
        list=findList(name);
        item->data=value;
        
        if(list!=NULL){
            list_sort(list, lessList, NULL);
            list_insert_ordered(list, &(item->elem), lessList, NULL);
        }
    }
    else if(!strcmp(command, "list_empty")){
        scanf("%s",name);
        list=findList(name);

        if(list!=NULL){
            if(list_empty(list))
              printf("true\n");
            else
              printf("false\n");
        }
    }
    else if(!strcmp(command, "list_size")){
        scanf("%s",name);
        list=findList(name);

        if(list!=NULL)
          printf("%d\n",(int)list_size(list));
    }
    else if(!strcmp(command, "list_max")){
        listMinMax(0);
    }
    else if(!strcmp(command, "list_min")){
        listMinMax(1);
    }
    else if(!strcmp(command, "list_remove")){
        int position;
        scanf("%s %d",name, &position);
        list=findList(name);

        if(list!=NULL){
            e=list_begin(list);
            for(int i=0;i<position;i++){
                e=list_next(e);
            }

            list_remove(e);
        }
    }
    else if(!strcmp(command, "list_reverse")){
        scanf("%s",name);
        list=findList(name);

        if(list!=NULL)
          list_reverse(list);
    }
    else if(!strcmp(command, "list_shuffle")){
    }
    else if(!strcmp(command, "list_sort")){
        scanf("%s",name);
        list=findList(name);

        if(list!=NULL)
            list_sort(list, lessList, NULL);
    }
    else if(!strcmp(command, "list_splice")){
        int start, end, position;
        char* targetName=(char*)malloc(sizeof(char)*MAX_NAME_LENGTH);
        struct list_elem* first;
        struct list_elem* last;
        struct list* target;

        scanf("%s %d",name,&position);
        scanf("%s %d %d",targetName, &start, &end);
        list=findList(name);
        target=findList(targetName);

        if(list!=NULL && target!=NULL){
            e=list_begin(list);
            first=list_begin(target);
            last=list_begin(target);

            for(int i=0;i<position;i++)
              e=list_next(e);
            for(int i=0;i<start; i++)
              first=list_next(first);
            for(int i=0;i<end;i++)
              last=list_next(last);

            list_splice(e, first, last);
        }

    }
    else if(!strcmp(command, "list_swap")){
    }
    else if(!strcmp(command, "list_unique")){
        char tok[2*MAX_NAME_LENGTH+1];
        char* dup=(char*)malloc(sizeof(char)*MAX_NAME_LENGTH);
        struct list* dupList;

        scanf("%[^\n]s",tok);
        name=strtok(tok, " ");
        dup=strtok(NULL, " ");
        list=findList(name);

        if(dup==NULL){
            if(list!=NULL)
              list_unique(list, NULL, lessList, NULL);
        }
        else{
            dupList=findList(dup);

            if(list!=NULL && dupList!=NULL)
              list_unique(list, dupList, lessList, NULL);
        }
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

struct list* findList(char* name){
    for(int i=0;i<10;i++){
        if(!strcmp(testList[i].name, name)) 
          return testList[i].start;
    }

    return NULL;
}

void listPush(int idx){
    struct list* list;
    struct list_item* item=(struct list_item*)malloc(sizeof(struct list_item));
    char* name=(char*)malloc(sizeof(char)*MAX_NAME_LENGTH);
    int temp;

    scanf("%s %d",name, &temp);
    list=findList(name);

    if(list==NULL) return;

    item->data=temp;
    if(idx)
      list_push_front(list, &(item->elem));
    else
      list_push_back(list, &(item->elem));
}

void listFrontBack(int idx){
    struct list* list;
    struct list_elem* e;
    struct list_item* item;
    char* name=(char*)malloc(sizeof(char)*MAX_NAME_LENGTH);

    scanf("%s",name);
    list=findList(name);

    if(list!=NULL){
        if(idx)
          e=list_back(list);
        else
          e=list_front(list);
    }
    else return;
        
    item=list_entry(e, struct list_item, elem);
    printf("%d\n",item->data);
}

void listPop(int idx){
    struct list* list;
    struct list_elem* e;
    char* name=(char*)malloc(sizeof(char)*MAX_NAME_LENGTH);

    scanf("%s",name);
    list=findList(name);

    if(list!=NULL){
        if(idx)
          e=list_pop_front(list);
        else
          e=list_pop_back(list);
    }
    else return;
}

void listMinMax(int idx){
    struct list* list;
    struct list_elem* e;
    struct list_item* item=(struct list_item*)malloc(sizeof(struct list_item));
    char* name=(char*)malloc(sizeof(char)*MAX_NAME_LENGTH);

    scanf("%s",name);
    list=findList(name);

    if(list!=NULL){
        if(idx)
          e=list_min(list, lessList, NULL);
        else
          e=list_max(list, lessList, NULL);

        item=list_entry(e,struct list_item, elem);
        printf("%d\n",item->data);
    }
}

bool lessList(const struct list_elem* a, const struct list_elem* b, void* aux){
    struct list_item* itema=list_entry(a, struct list_item, elem);
    struct list_item* itemb=list_entry(b, struct list_item, elem);

    return itema->data < itemb->data;
}

int main(){
    int i,j;
    char command[MAX_COMMAND_LENGTH];
    char commandCopy[MAX_COMMAND_LENGTH];
    char kind[MAX_KIND_LENGTH];
    char* name=(char*)malloc(sizeof(char)*MAX_NAME_LENGTH);
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
