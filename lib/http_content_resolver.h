#ifndef NEW_H
#define NEW_H
#include <stdio.h>

typedef struct {
	char *header_content;
	size_t header_size;
} ResponseHeader;

char *get_file_content(FILE *file, size_t file_size);
FILE *get_resource_ptr(char *resource);
size_t get_file_size(FILE *file);
int is_valid_route(char *uri);
ResponseHeader *get_response_header(char *resource_extension, char *uri);

#endif // NEW_H
