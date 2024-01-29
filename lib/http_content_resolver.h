#ifndef NEW_H
#define NEW_H
#include <stdio.h>

struct Header_Info {
	char* header_content;
	size_t header_size;
};

char* get_file_content(FILE* file, int file_size);
FILE* get_resource_ptr(char* resource);
int get_file_size(FILE* file);
int is_valid_route(char* uri);
	struct Header_Info* get_response_header(char* extention, char* uri);

#endif // NEW_H
