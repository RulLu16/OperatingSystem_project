#include "main.h"

void listCommand(char command[]){
    char* name=(char*)malloc(sizeof(char)*MAX_NAME_LENGTH);
    struct list* list;
    struct list_elem* e;
    struct list_item* item;

    if(strcmp(command, "list_unique")){
        scanf("%s", name);
        list = findList(name);

        if(list==NULL) return;
    }

    if(!strcmp(command, "list_push_back")){
        int temp;
        item = (struct list_item*)malloc(sizeof(struct list_item));

        scanf("%d", &temp);
        item->data = temp;

        list_push_back(list, &(item->elem));
    }
    else if(!strcmp(command, "list_push_front")){
        int temp;
        item = (struct list_item*)malloc(sizeof(struct list_item));

        scanf("%d", &temp);
        item->data = temp;

        list_push_front(list, &(item->elem));
    }
    else if(!strcmp(command, "list_front")){
        e = list_front(list);
        printf("%d\n", list_entry(e, struct list_item, elem)->data);
    }
    else if(!strcmp(command, "list_back")){
        e = list_back(list);
        printf("%d\n", list_entry(e, struct list_item, elem)->data);
    }
    else if(!strcmp(command, "list_pop_back")){
        e = list_pop_back(list);
    }
    else if(!strcmp(command, "list_pop_front")){
        e = list_pop_front(list);
    }
    else if(!strcmp(command, "list_insert")){
        item=(struct list_item*)malloc(sizeof(struct list_item));
        int position, value;

        scanf("%d %d",&position, &value);

        e=searchListIndex(list, position);
        item->data=value;

        list_insert(e, &(item->elem));
    }
    else if(!strcmp(command, "list_insert_ordered")){
        item=(struct list_item*)malloc(sizeof(struct list_item));
        int value;

        scanf("%d", &value);
        item->data=value;
        list_sort(list, lessList, NULL);
        list_insert_ordered(list, &(item->elem), lessList, NULL);    
    }
    else if(!strcmp(command, "list_empty")){
        if(list_empty(list))
          printf("true\n");
        else
          printf("false\n");
    }
    else if(!strcmp(command, "list_size")){
        printf("%zu\n",list_size(list));
    }
    else if(!strcmp(command, "list_max")){
        e = list_max(list, lessList, NULL);
        printf("%d\n", list_entry(e, struct list_item, elem)->data);
    }
    else if(!strcmp(command, "list_min")){
        e = list_min(list, lessList, NULL);
        printf("%d\n", list_entry(e, struct list_item, elem)->data);
    }
    else if(!strcmp(command, "list_remove")){
        int position;

        scanf("%d",&position);
        e=searchListIndex(list, position);
        list_remove(e);
    }
    else if(!strcmp(command, "list_reverse")){
        list_reverse(list);
    }
    else if(!strcmp(command, "list_shuffle")){
        list_shuffle(list);
    }
    else if(!strcmp(command, "list_sort")){
        list_sort(list, lessList, NULL);
    }
    else if(!strcmp(command, "list_splice")){
        int start, end, position;
        char* targetName=(char*)malloc(sizeof(char)*MAX_NAME_LENGTH);

        scanf("%d", &position);
        scanf("%s %d %d",targetName, &start, &end);
        struct list* target=findList(targetName);

        if(target!=NULL){
            e=searchListIndex(list, position);
            struct list_elem* first=searchListIndex(target, start);
            struct list_elem* last=searchListIndex(target, end);

            list_splice(e, first, last);
        }
    }
    else if(!strcmp(command, "list_swap")){
        int first, second;

        scanf("%d %d",&first, &second);
        e=searchListIndex(list, first);
        struct list_elem* target=searchListIndex(list, second);

        list_swap(e, target);
    }
    else if(!strcmp(command, "list_unique")){
        char tok[2*MAX_NAME_LENGTH+1];
        char* dup=(char*)malloc(sizeof(char)*MAX_NAME_LENGTH);

        scanf("%[^\n]s",tok);
        name=strtok(tok, " ");
        dup=strtok(NULL, " ");
        list=findList(name);

        if(dup==NULL){
            if(list!=NULL)
              list_unique(list, NULL, lessList, NULL);
        }
        else{
            struct list* dupList=findList(dup);

            if(list!=NULL && dupList!=NULL)
              list_unique(list, dupList, lessList, NULL);
        }
    }
}

void hashCommand(char command[]){
    char* name = (char*)malloc(sizeof(char)*MAX_NAME_LENGTH);
    struct hash* hash;

    scanf("%s", name);
    hash = findHash(name);

    if(hash==NULL) return;
    
    if(!strcmp(command, "hash_insert")){
        int value;

        scanf("%d",&value);
        struct hash_item* item = (struct hash_item*)malloc(sizeof(struct hash_item));
        item->data = value;
        hash_insert(hash, &(item->elem));
    }
    else if(!strcmp(command, "hash_apply")){
        char condition[10];

        scanf("%s",condition);
        if(!strcmp(condition, "square"))
           hash_apply(hash, squareHashAction);
        else if(!strcmp(condition, "triple"))
          hash_apply(hash, tripleHashAction);
    }
    else if(!strcmp(command, "hash_delete")){
        int value;
        
        scanf("%d",&value);
        struct hash_item* item = (struct hash_item*)malloc(sizeof(struct hash_item));
        item->data = value;
        hash_delete(hash, &(item->elem));     
    }
    else if(!strcmp(command, "hash_empty")){
        if(hash_empty(hash))
          printf("true\n");
        else
          printf("false\n");
    }
    else if(!strcmp(command, "hash_size")){
        printf("%zu\n",hash_size(hash));
    }
    else if(!strcmp(command, "hash_clear")){
        hash_clear(hash, destructHashAction);
    }
    else if(!strcmp(command, "hash_find")){
        int value;

        scanf("%d",&value);
        struct hash_item* item = (struct hash_item*)malloc(sizeof(struct hash_item));
        item->data = value;
        struct hash_elem* e = hash_find(hash, &(item->elem));

        if(e!=NULL)
          printf("%d\n",hash_entry(e, struct hash_item, elem)->data);
    }
    else if(!strcmp(command, "hash_replace")){
        int value;

        scanf("%d",&value);
        struct hash_item* item = (struct hash_item*)malloc(sizeof(struct hash_item));
        item->data = value;
        hash_replace(hash, &(item->elem));
    }
}

void bitmapCommand(char command[]){
    char* name = (char*)malloc(sizeof(char)*MAX_NAME_LENGTH);
    struct bitmap* bitmap;
    size_t start, cnt;
    char boolean[10];

    scanf("%s", name);
    bitmap = findBitmap(name);

    if(bitmap==NULL) return;

    if(!strcmp(command, "bitmap_mark")){
        size_t idx;

        scanf("%zu", &idx);
        bitmap_mark(bitmap, idx);
    }
    else if(!strcmp(command, "bitmap_all")){
        scanf("%zu %zu",&start, &cnt);

        if(bitmap_all(bitmap, start, cnt))
          printf("true\n");
        else
          printf("false\n");
    }
    else if(!strcmp(command, "bitmap_any")){
        scanf("%zu %zu",&start, &cnt);

        if(bitmap_any(bitmap, start, cnt))
          printf("true\n");
        else
          printf("false\n");
    }
    else if(!strcmp(command, "bitmap_contains")){
        bool result;

        scanf("%zu %zu", &start, &cnt);
        scanf("%s", boolean);

        if(!strcmp(boolean, "true"))
          result = bitmap_contains(bitmap, start, cnt, true);
        else
          result = bitmap_contains(bitmap, start, cnt, false);

        if(result == true) printf("true\n");
        else printf("false\n");
    }
    else if(!strcmp(command, "bitmap_count")){
        scanf("%zu %zu",&start, &cnt);
        scanf("%s", boolean);

        if(!strcmp(boolean, "true"))
          printf("%zu\n",bitmap_count(bitmap, start, cnt, true));
        else
          printf("%zu\n",bitmap_count(bitmap, start, cnt, false));
    }
    else if(!strcmp(command, "bitmap_dump")){
        bitmap_dump(bitmap);
    }
    else if(!strcmp(command, "bitmap_expand")){
        int size, i;

        scanf("%d",&size);
        for(i=0;i<10;i++){
            if(!strcmp(testBitmap[i].name, name))
              break;
        }
        testBitmap[i].start = bitmap_expand(testBitmap[i].start, size);
    }
    else if(!strcmp(command, "bitmap_flip")){
        scanf("%zu", &start);

        bitmap_flip(bitmap, start);
    }
    else if(!strcmp(command, "bitmap_none")){
        scanf("%zu %zu",&start, &cnt);

        if(bitmap_none(bitmap, start, cnt))
          printf("true\n");
        else printf("false\n");
    }
    else if(!strcmp(command, "bitmap_reset")){
        scanf("%zu", &start);

        bitmap_reset(bitmap, start);
    }
    else if(!strcmp(command, "bitmap_scan")){
        scanf("%zu %zu", &start, &cnt);
        scanf("%s", boolean);

        if(!strcmp(boolean, "true"))
          printf("%zu\n",bitmap_scan(bitmap, start, cnt, true));
        else
          printf("%zu\n",bitmap_scan(bitmap, start, cnt, false));
    }
    else if(!strcmp(command, "bitmap_scan_and_flip")){
        scanf("%zu %zu",&start, &cnt);
        scanf("%s", boolean);

        if(!strcmp(boolean, "true"))
          printf("%zu\n", bitmap_scan_and_flip(bitmap, start, cnt, true));
        else
          printf("%zu\n", bitmap_scan_and_flip(bitmap, start, cnt, false));
    }
    else if(!strcmp(command, "bitmap_set")){
        scanf("%zu %s",&start, boolean);

        if(!strcmp(boolean, "true"))
          bitmap_set(bitmap, start, true);
        else
          bitmap_set(bitmap, start, false);
    }
    else if(!strcmp(command, "bitmap_set_all")){
        scanf("%s",boolean);

        if(!strcmp(boolean, "true"))
          bitmap_set_all(bitmap, true);
        else
          bitmap_set_all(bitmap, false);
    }
    else if(!strcmp(command, "bitmap_set_multiple")){
        scanf("%zu %zu",&start, &cnt);
        scanf("%s", boolean);

        if(!strcmp(boolean, "true"))
          bitmap_set_multiple(bitmap,start, cnt, true);
        else
          bitmap_set_multiple(bitmap,start, cnt, false);
    }
    else if(!strcmp(command, "bitmap_size")){
        printf("%zu\n",bitmap_size(bitmap));
    }
    else if(!strcmp(command, "bitmap_test")){
        scanf("%zu", &start);

        if(bitmap_test(bitmap, start))
          printf("true\n");
        else
          printf("false\n");
    }
}

struct list* findList(char* name){
    for(int i=0;i<10;i++){
        if(!strcmp(testList[i].name, name)) 
          return testList[i].start;
    }

    return NULL;
}

struct list_elem* searchListIndex(struct list* list, int index){
    struct list_elem* e=list_begin(list);

    for(int i=0;i<index;i++)
      e=list_next(e);

    return e;
}

bool lessList(const struct list_elem* a, const struct list_elem* b, void* aux){
    struct list_item* itema=list_entry(a, struct list_item, elem);
    struct list_item* itemb=list_entry(b, struct list_item, elem);

    return itema->data < itemb->data;
}

bool lessHash(const struct hash_elem* a, const struct hash_elem* b, void* aux){
    struct hash_item* itema = hash_entry(a, struct hash_item, elem);
    struct hash_item* itemb = hash_entry(b, struct hash_item, elem);

    return itema->data < itemb->data;
}

unsigned hashFunc(const struct hash_elem* e, void* aux){
    return hash_int((int)hash_entry(e, struct hash_item, elem)->data);
}

struct hash* findHash(char* name){
    for(int i=0;i<10;i++){
        if(!strcmp(testHash[i].name, name))
          return testHash[i].start;
    }

    return NULL;
}

void squareHashAction(struct hash_elem* e, void* aux){
    struct hash_item* item = hash_entry(e, struct hash_item, elem);
    item->data = item->data * item->data;
}

void tripleHashAction(struct hash_elem* e, void* aux){
    struct hash_item* item = hash_entry(e, struct hash_item, elem);
    item->data = item->data * item->data * item->data;
}

void destructHashAction(struct hash_elem* e, void* aux){
    struct hash_item* item = hash_entry(e, struct hash_item, elem);
    free(item);
}

struct bitmap* findBitmap(char* name){
    for(int i=0;i<10;i++){
        if(!strcmp(testBitmap[i].name, name))
          return testBitmap[i].start;
    }

    return NULL;
}

int main(){
    int i;
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
                for(int i=0;i<10;i++){
                    if(testList[i].start==NULL){
                        strcpy(testList[i].name, name);
                        testList[i].start=(struct list*)malloc(sizeof(struct list));
                        list_init(testList[i].start);
                        break;
                    }
                }                        
            }
            //====== create list =======

            else if(!strcmp(kind, "hashtable")){
                scanf("%s", name);
                for(i=0;i<10;i++){
                    if(testHash[i].start == NULL){
                        strcpy(testHash[i].name, name);
                        testHash[i].start = (struct hash*)malloc(sizeof(struct hash));
                        hash_init(testHash[i].start, hashFunc, lessHash, NULL);
                        break;
                    }
                }
            }
            //====== create hash =======

            else if(!strcmp(kind, "bitmap")){
                size_t size;
                scanf("%s %zu",name, &size);

                for(i=0;i<10;i++){
                    if(testBitmap[i].start==NULL){
                        strcpy(testBitmap[i].name, name);
                        testBitmap[i].start = bitmap_create(size);
                        break;
                    }
                }
            }
            //====== create bitmap =====
        }
        else if(!strcmp(command, "dumpdata")){
            struct list* list;
            struct hash* hash;
            struct bitmap* bitmap;

            scanf("%s",name);

            list=findList(name);
            hash=findHash(name);
            bitmap=findBitmap(name);
            if(list!=NULL){
                for(struct list_elem* e=list_begin(list); e!=list_end(list); e=list_next(e)){
                    struct list_item* item=list_entry(e, struct list_item, elem);
                    printf("%d ",item->data);
                }
                printf("\n");
            }
            //======= print list ========
            else if(hash!=NULL){
                struct hash_iterator* it = (struct hash_iterator*)malloc(sizeof(struct hash_iterator));
                hash_first(it, hash);
                for(it;hash_next(it)!=NULL;){
                    printf("%d ", hash_entry(it->elem, struct hash_item, elem)->data);
                }
                printf("\n");
            }
            //======= print hash ========
            else if(bitmap!=NULL){
                for(i=0;i<(int)bitmap_size(bitmap);i++)
                  printf("%d",(int)bitmap_test(bitmap, (size_t)i));
                printf("\n");
            }
            //======= print bitmap ======
        }
        else if(!strcmp(command, "delete")){
            struct list* list;
            struct hash* hash;
            struct bitmap* bitmap;

            scanf("%s",name);

            list=findList(name);
            hash=findHash(name);
            bitmap=findBitmap(name);
            if(list!=NULL){
                for(i=0;i<10;i++){
                    if(!strcmp(testList[i].name, name))
                      break;
                }
                for(struct list_elem* e = list_begin(list); e!=list_end(list); e = list_remove(e));
                testList[i].start = NULL; 
                strcpy(testList[i].name, "");
            }
            //======== delete list =========
            else if(hash!=NULL){
                for(i=0;i<10;i++){
                    if(!strcmp(testHash[i].name, name))
                      break;
                }
                hash_destroy(hash, destructHashAction);
                testHash[i].start = NULL;
                strcpy(testHash[i].name, "");
            }
            //======== delete hash =========
            else if(bitmap!=NULL){
                for(i=0;i<10;i++){
                    if(!strcmp(testBitmap[i].name, name))
                      break;
                }
                bitmap_destroy(bitmap);
                testBitmap[i].start = NULL;
                strcpy(testBitmap[i].name, "");
            }
            //======== delete bitmap =======
        }
        else if(!strcmp(commandKind, "list")){
            listCommand(command);
        }
        //========= list command ========
        else if(!strcmp(commandKind, "hash")){
            hashCommand(command);
        }
        //========= hash command ========
        else if(!strcmp(commandKind, "bitmap")){
            bitmapCommand(command);
        }
        //========= bitmap command ======
    }
}
