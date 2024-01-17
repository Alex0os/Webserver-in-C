#ifndef NEW_H
#define NEW_H
#include <stdio.h>

struct Header_Info {
	char* header_content;
	size_t header_size;
};

char* file_content(FILE* file, int file_size);
int get_file_size(FILE* file);
int is_valid_route(char* uri);
struct Header_Info* get_content_type(char* extention);

#endif // NEW_H
