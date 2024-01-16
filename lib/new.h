#ifndef NEW_H
#define NEW_H
#include <stdio.h>

struct Header_Info {
	char* header_content;
	size_t header_size;
};

char* file_content(FILE* file, int file_size);
int get_file_size(FILE* file);
struct Header_Info* definir_tipo_y_subtipo(char* extention);

#endif // NEW_H
