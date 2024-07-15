#ifndef NEW_H
#define NEW_H
#include <stdio.h>

typedef struct {
	char* header_content;
	size_t header_size;
} LineInfo;

char* get_file_content(FILE* file, int file_size);
FILE* get_resource_ptr(char* resource);
int get_file_size(FILE* file);
int is_valid_route(char* uri);
LineInfo* get_response_line(char* extention, char* uri);

#endif // NEW_H
