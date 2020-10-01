#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitmap.h"
#include "debug.h"
#include "hash.h"
#include "hex_dump.h"
#include "limits.h"
#include "list.h"
#include "round.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_KIND_LENGTH 20
#define MAX_NAME_LENGTH 50

struct list_item{
    struct list_elem elem;
    int data;
};

struct hash_item{
    struct hash_elem elem;
    int data;
};

typedef struct{
    struct list* start;
    char name[50];
}L_List;

typedef struct{
    struct hash* start;
    char name[50];
}H_List;

typedef struct{
    struct bitmap* start;
    char name[50];
}B_List;

L_List testList[10];
H_List testHash[10];
B_List testBitmap[10];

void listCommand(char[]);
void hashCommand(char[]);
void bitmapCommand(char[]);

struct list* findList(char*);
struct list_elem* searchListIndex(struct list*, int);
bool lessList(const struct list_elem*, const struct list_elem*, void*);
bool lessHash(const struct hash_elem*, const struct hash_elem*, void*);
unsigned hashFunc(const struct hash_elem*, void*);
struct hash* findHash(char*);
void squareHashAction(struct hash_elem*, void*);
void tripleHashAction(struct hash_elem*, void*);
void destructHashAction(struct hash_elem*, void*);
