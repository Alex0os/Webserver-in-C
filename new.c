#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct Header_Info {
	char* header_content;
	size_t header_size;
};

struct Header_Info* get_content_subtype(char* extention, char* main_type);
char* get_content_type(char* uri);
char* file_content(FILE* file, int file_size);
int get_file_size(FILE* file);


struct Header_Info* get_content_subtype(char* extention, char* uri){
	char* main_type = get_content_type(uri);

	struct Header_Info* header = (struct Header_Info*)malloc(sizeof(struct Header_Info));

	header->header_content = (char*)malloc(1000);
	sprintf(header->header_content, main_type, extention + 1);
	header->header_size = strlen(header->header_content);

	return header;
}


char* get_content_type(char* uri){
	if (strstr(uri, "images") != NULL) {
		return "HTTP/1.1 200 OK\r\nContent-Type: image/%s\r\n\r\n";
	}
	return "HTTP/1.1 200 OK\r\nContent-Type: text/%s\r\n\r\n";
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


char* get_resource_route(char* resource){
	char current_dir[512];
	getcwd(current_dir, 256);

	char* resource_route = (char*)malloc(512);
	sprintf(resource_route, "%s/src%s",current_dir, resource);

	return resource_route;
}
