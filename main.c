#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "lib/Http_server.h"
#include "lib/routing.h"
#include "lib/http_content_resolver.h"
#include "lib/urls.h"

typedef struct _ResponseBuffer {
	char* buffer_content;
	int buffer_size;
} ResponseBuffer;

char* get_resource_info(Hash_Table* table, char* route);
ResponseBuffer* response_buffer(char* resource);

//

char* get_resource_info(Hash_Table* table, char* route){
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
	return resource_content->resource;
}


ResponseBuffer* response_buffer(char* resource){
	FILE* resource_ptr = get_resource_ptr(resource);

	if (resource_ptr == NULL) {
		perror("The resource was not found");
		return NULL;
	}

	int file_size = get_file_size(resource_ptr);
	char* file_content = get_file_content(resource_ptr, file_size);

	struct Header_Info* header = get_response_header(strchr(resource, '.'), resource);
	char* full_response = (char*)malloc(file_size + header->header_size + 1);


	sprintf(full_response, "%s%s", header->header_content, file_content);

	fclose(resource_ptr);
	free(file_content);
	free(header);

	ResponseBuffer* buffer = (ResponseBuffer*)malloc(sizeof(ResponseBuffer));

	buffer->buffer_content = full_response;
	buffer->buffer_size = strlen(full_response);
	return buffer;
}


int main(void){
	Hash_Table* routes_resources_table = defining_routes();
	Http_server http_server;

	if (create_server(&http_server) < 0){
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
			char* resource_linked_to_route = get_resource_info(routes_resources_table, uri);
			response = response_buffer(resource_linked_to_route);
		}

		if (response == NULL) {
			continue;
		}

		send_response(client_socket, response->buffer_content, response->buffer_size);
		free(response);
		free(uri);
	}
	return EXIT_SUCCESS;
}
