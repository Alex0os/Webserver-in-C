#ifndef ROUTING_H
#define ROUTING_H

#include <stddef.h>

typedef struct _item {
	char *route;
	char *resource;
	struct _item *next_link;
} Item;

typedef struct _hash_table {
	Item **items;
	size_t table_size;
} HashTable;


int hash_function(char *route);
HashTable *create_table();
void create_route(HashTable *table, char *route, char *resource);
void handle_collision(Item *item, char *route, char *resource);
void print_table(HashTable *table);
void printchain(Item *item);
char *resource_folder(char *resource);


#endif // ROUTING_H
