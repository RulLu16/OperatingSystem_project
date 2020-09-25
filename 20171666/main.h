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
    struct list_elem;
    int data;
}

struct list* testList;
struct hash* testHash;
struct bitmap* testBitmap;

void listCommand(char[]);
void hashCommand(char[]);
void bitmapCommand(char[]);

