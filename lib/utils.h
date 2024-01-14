#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

struct Files_List {
	char** list;
	size_t size;
	int counter;
};

struct File_Info {
	FILE* file_pointer;
	size_t file_size;
};

struct File_Info* get_file_info(char* file_name);
char* get_file_content(struct File_Info* file_info);
struct Files_List* open_source_dir();

#endif // UTILS_H
