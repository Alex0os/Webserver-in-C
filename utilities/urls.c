#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "../lib/routing.h"

HashTable *defining_routes()
{
	HashTable *linked_routes = create_table();
	create_route(linked_routes, "/", "/index.html");

	return linked_routes;
}


