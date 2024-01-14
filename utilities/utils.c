#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIR_NAME_SIZE 512
#define MAX_AMOUNT_FILES 100

struct Files_List {
	char** list;
	size_t size;
	int counter;
};

struct File_Info {
	FILE* file_pointer;
	size_t file_size;
};


struct Files_List* open_source_dir();
struct File_Info* get_file_info(char* file_name);
char* get_file_content(struct File_Info* file_info);


struct File_Info* get_file_info(char* file_name){
	struct File_Info* file_info = malloc(sizeof(struct File_Info));
	char file_route[MAX_DIR_NAME_SIZE] = "/home/Matixannder/Desktop/Projects/LearningC/WebserverC/src/";
	strcat(file_route, file_name);


	FILE* file_pointer = fopen(file_route, "r");
	if (file_pointer == NULL) {
		perror("A problem trying to open the file");
	}

	fseek(file_pointer, 0, SEEK_END);
	ssize_t size = ftell(file_pointer);
	if (size < 0) {
		perror("A problem ocurred while trying to get the file size");
	}
	rewind(file_pointer);

	file_info->file_size = (size_t)size;
	file_info->file_pointer = file_pointer;

	return file_info;
}


char* get_file_content(struct File_Info* file_info){
	char* buffer = (char*)malloc(file_info->file_size + 1);

	fread(buffer, 1, file_info->file_size, file_info->file_pointer);

	buffer[file_info->file_size] = '\0';

	fclose(file_info->file_pointer);
	free(file_info);
	return buffer;
}


void get_dir_files(char* dir_name, struct Files_List* file_struct){
	char directory[MAX_DIR_NAME_SIZE] = "/home/Matixannder/Desktop/Projects/LearningC/WebserverC/src/";
	strcat(directory, dir_name);

	DIR* sub_dir = opendir(directory);
    if (sub_dir == NULL) {
        perror("Error al abrir el sub-directorio");
				return;
    }

	struct dirent *files;

	while ((files = readdir(sub_dir)) != NULL) {
		if (strcmp(files->d_name, ".") == 0 || strcmp(files->d_name, "..") == 0) {
			continue;
		}
		char* parent_dir = (char*)malloc(MAX_DIR_NAME_SIZE);
		strcpy(parent_dir, dir_name);
		strcat(parent_dir, "/");
		strcat(parent_dir, files->d_name);

		if (file_struct->counter == file_struct->size) {
			printf("There is no more space left in the files list\n");
		}
		file_struct->list[file_struct->counter] = parent_dir;
		file_struct->counter++;

	}
	closedir(sub_dir);
}


struct Files_List* open_source_dir(){
	struct Files_List* list_struct = (struct Files_List*)malloc(sizeof(struct Files_List));

	const char *ruta = "/home/Matixannder/Desktop/Projects/LearningC/WebserverC/src";

	struct dirent *entrada;

	DIR *directorio = opendir(ruta);

	if (directorio == NULL) {
		perror("Error al abrir el directorio");
		return NULL;
	}

	list_struct->list = (char**)calloc(MAX_AMOUNT_FILES, sizeof(char*));
	list_struct->counter = 0;
	list_struct->size = MAX_AMOUNT_FILES;

	while ((entrada = readdir(directorio)) != NULL) {
		if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
			continue;
		}

		if (strchr(entrada->d_name, '.') == NULL) {
			get_dir_files(entrada->d_name, list_struct);
		}
	}
	closedir(directorio);
	return list_struct;
}
