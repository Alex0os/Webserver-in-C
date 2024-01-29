#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "lib/routing.h"

Hash_Table* defining_routes(){
	Hash_Table* linked_routes = create_table();
	create_route(linked_routes, "/", "/index.html");

	return linked_routes;
}


