#ifndef ROUTING_H
#define ROUTING_H

#include <stddef.h>

typedef struct _item {
	char* route;
	char* resource;
	struct _item* next_link;
} Item;

typedef struct _hash_table {
	Item** items;
	size_t table_size;
} Hash_Table;


int hash_function(char* route);
Hash_Table* create_table();
void create_route(Hash_Table* table, char* route, char* resource);
void handle_collision(Item* item, char* route, char* resource);
void print_table(Hash_Table* table){
void printchain(Item* item);
char* resource_folder(char* resource);


#endif // ROUTING_H
