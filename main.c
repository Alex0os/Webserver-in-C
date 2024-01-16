#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lib/Http_server.h"
#include "lib/routing.h"
#include "lib/new.h"
#include "lib/utils.h"

#define BUFFER_SIZE 10000

typedef struct _ResponseBuffer {
	char* buffer_content;
	int buffer_size;
} ResponseBuffer;


void defining_routes(){
	Hash_Table* linked_routes = create_table();
	create_route(linked_routes, "/", "src/index.html");
	print_table(linked_routes);
}

void defining_files(){
	Hash_Table* linked_files = create_table();

	struct Files_List* files_list = open_source_dir();
	for (int i = 0; i < files_list->counter; i++) {
		char* file_content = get_file_content(get_file_info(files_list->list[i]));

		create_route(linked_files, files_list->list[i], file_content);
	}
	print_table(linked_files);
}


ResponseBuffer* response_buffer(char* resource){

	FILE* file_ptr = fopen(resource, "r");
	if (file_ptr == NULL) {
		return NULL;
	}

	int html_size = file_size(file_ptr);
	char* html_content = file_content(file_ptr, html_size);

	struct Header_Info* header = definir_tipo_y_subtipo(strchr(resource, '.'));
	char* full_response = (char*)malloc(html_size + header->header_size + 1);


	strcpy(full_response, header->header_content);
	strcat(full_response, html_content);

	fclose(file_ptr);
	free(html_content);
	free(header);

	ResponseBuffer* buffer = (ResponseBuffer*)malloc(sizeof(ResponseBuffer));

	buffer->buffer_content = full_response;
	buffer->buffer_size = strlen(full_response);


	return buffer;
}

void imprime(char* resource){
	ResponseBuffer* response = response_buffer(resource);
	if (response == NULL) {
		printf("Se ha generado un error, no existe %s en la aplicacioń\n", resource);
		return;
	}
	printf("Contenido de %s ---> %s\n", resource, response->buffer_content);
	free(response);
	return;
}

int main(void)
{
	imprime("src/index.html");
	imprime("src/styles/style.css");
	return 0;
}
//	defining_files();
//	Http_server http_server;
//
//	if (create_socket(&http_server) < 0){
//		exit(EXIT_FAILURE);
//	}
//
//
//	for (;;) {
//
//		//ResponseBuffer* response = response_buffer();
//		//handle_client(http_server.socket, response->buffer_content, response->buffer_size);
//
//	}
//
//	return EXIT_SUCCESS;
//}
