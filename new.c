#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct Header_Info {
	char* header_content;
	size_t header_size;
};

struct Header_Info* get_content_type(char* extention);
char* file_content(FILE* file, int file_size);
int get_file_size(FILE* file);


struct Header_Info* get_content_type(char* extention){
	struct Header_Info* header = (struct Header_Info*)malloc(sizeof(struct Header_Info));

	header->header_content = (char*)malloc(1000);
	sprintf(header->header_content, "HTTP/1.1 200 OK\r\nContent-Type: text/%s\r\n\r\n", extention + 1);
	header->header_size = strlen(header->header_content);

	return header;
}

int get_file_size(FILE* file){
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

int is_valid_route(char* uri){
	if (strchr(uri, '.')) {
		return 0;
	}
	return 1;
}


