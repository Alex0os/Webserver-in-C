#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define MAX_EXTENTION_SIZE 100


typedef struct _item {
	char* route;
	char* resource;
	struct _item* next_link;
} Item;

typedef struct _hash_table {
	Item** items;
	size_t table_size;
} Hash_Table;


char* resource_folder(char* resource){
	int char_index = 0;

	for (int i = 0; resource[char_index]; i++) {
		if (resource[char_index] == '.') {
			char* resource_extention = malloc(MAX_EXTENTION_SIZE);
			strcpy(resource_extention, &resource[char_index]);
			return resource_extention;
		}
	}
	return NULL;
}

int hash_function(char* route){
	size_t hash_index = 0;
	for (size_t i = 0; route[i]; i++) {
		hash_index += route[i] * (pow(2, i));
	}
	return hash_index % (size_t)TABLE_SIZE;
}

Hash_Table* create_table(){
	Hash_Table* table = malloc(sizeof(Hash_Table));
	table->table_size = TABLE_SIZE;

	table->items = (Item**)calloc(TABLE_SIZE, sizeof(Item*));

	for (size_t i = 0; i < table->table_size; i++) {
		table->items[i] = NULL;
	}

	return table;
}

void handle_collision(Item* item, char* route, char* resource){
	while (item->next_link != NULL) {
		item = item->next_link;
	}
	item->next_link = (Item*)malloc(sizeof(Item));

	item->next_link->route = route;
	item->next_link->resource  = resource;
	item->next_link->next_link = NULL;
}

void create_route(Hash_Table* table, char* route, char* resource){
	size_t i = hash_function(route);

	if (table->items[i] != NULL) {
		handle_collision(table->items[i], route, resource);
		return;
	}

	table->items[i] = (Item*)malloc(sizeof(Item));

	table->items[i]->route = route;
	table->items[i]->resource  = resource;
	table->items[i]->next_link = NULL;
}

void printchain(Item* item){
	do {
		printf("Key: %s\nValue: %s\n\n", item->route, item->resource);
		item = item->next_link;
	} while (item != NULL);
}

void print_table(Hash_Table* table){
	for (int i = 0; i < table->table_size; i++) {
		if (table->items[i] == NULL) {
			continue;
		}
		if (table->items[i]->next_link != NULL) {
			printchain(table->items[i]);
		} else {
			printf("Key: %s\nValue: %s\n\n", table->items[i]->route, table->items[i]->resource);
		}
	}
}

