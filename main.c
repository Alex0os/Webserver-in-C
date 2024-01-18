#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "lib/Http_server.h"
#include "lib/routing.h"
#include "lib/new.h"

typedef struct _ResponseBuffer {
	char* buffer_content;
	int buffer_size;
} ResponseBuffer;


Hash_Table* defining_routes();
ResponseBuffer* get_resource_info(Hash_Table* table, char* route);
ResponseBuffer* response_buffer(char* resource);

Hash_Table* defining_routes(){
	Hash_Table* linked_routes = create_table();
	create_route(linked_routes, "/", "/index.html");

	return linked_routes;
}


ResponseBuffer* get_resource_info(Hash_Table* table, char* route){
	int i = hash_function(route);
	Item* resource_content = table->items[i];

	if (resource_content == NULL) {
		return NULL;
	}

	while (strcmp(resource_content->route, route) != 0) {
		if ((resource_content = resource_content->next_link) == NULL) {
			return NULL;
		}
	}

	return response_buffer(resource_content->resource);
}

ResponseBuffer* response_buffer(char* resource){
	char* resource_route = get_resource_route(resource);

	FILE* file_ptr = fopen(resource_route, "r");
	if (file_ptr == NULL) {
		perror("The resource was not found");
		return NULL;
	}

	int html_size = get_file_size(file_ptr);
	char* html_content = file_content(file_ptr, html_size);

	struct Header_Info* header = get_content_subtype(strchr(resource, '.'), resource);
	char* full_response = (char*)malloc(html_size + header->header_size + 1);


	strcpy(full_response, header->header_content);
	strcat(full_response, html_content);

	fclose(file_ptr);
	free(resource_route);
	free(html_content);
	free(header);

	ResponseBuffer* buffer = (ResponseBuffer*)malloc(sizeof(ResponseBuffer));

	buffer->buffer_content = full_response;
	buffer->buffer_size = strlen(full_response);
	return buffer;
}


int main(void){
	Hash_Table* routes_resources_table = defining_routes();
	Http_server http_server;

	if (create_socket(&http_server) < 0){
		exit(EXIT_FAILURE);
	}

	for (;;) {
		int client_socket = handle_client(http_server.socket);

		char* uri = get_request_header(client_socket);
		ResponseBuffer* response;

		if (strchr(uri, '.')) {
			// If a dot is in the "uri", then it is a file route, so is not necessary to look for it in the table of defined valid routes
			response = response_buffer(uri);
		} else {
			response = get_resource_info(routes_resources_table, uri);
		}

		if (response == NULL) {
			printf("The uri '%s' didn't return any resource content, not resource found", uri);
			continue;
		}

		send_response(client_socket, response->buffer_content, response->buffer_size);
		free(response);
	}
	return EXIT_SUCCESS;
}
