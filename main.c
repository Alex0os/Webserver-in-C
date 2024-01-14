#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lib/Http_server.h"
#include "lib/routing.h"
#include "lib/utils.h"

#define BUFFER_SIZE 10000

typedef struct _ResponseBuffer {
	char* buffer_content;
	int buffer_size;
} ResponseBuffer;

int file_size(FILE* file){
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	return size;
}

char* file_content(FILE* file, int file_size){
	char* file_content = malloc(file_size + 1);
	fread(file_content, 1, file_size, file);

	return file_content;
}

ResponseBuffer response_buffer(){

	FILE* html_file = fopen("src/index.html", "r");
	int html_size = file_size(html_file);
	char* html_content = file_content(html_file, html_size);

	char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
	char* full_response = (char*)malloc(html_size + strlen(response) + 1);


	strcpy(full_response, response);
	strcat(full_response, html_content);

	free(html_file);
	free(html_content);

	ResponseBuffer buffer;

	buffer.buffer_content = full_response;
	buffer.buffer_size = strlen(full_response);

	return buffer;
}


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


int main(void)
{
	defining_files();


	return 0;
	Http_server http_server;

	if (create_socket(&http_server) < 0){
		exit(EXIT_FAILURE);
	}


	for (;;) {

		ResponseBuffer response = response_buffer();
		handle_client(http_server.socket, response.buffer_content, response.buffer_size);

	}

	return EXIT_SUCCESS;
}
