#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct File_Info {
	FILE* file_pointer;
	size_t file_size;
};


// Now I need a function that recieves the file name sent by the request 
struct File_Info* get_file_info(char* file_name);
void read_file_content(struct File_Info* file_info);


struct File_Info* get_file_info(char* file_name){
	struct File_Info* file_info = malloc(sizeof(struct File_Info));

	FILE* file_pointer = fopen(file_name, "r");
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


void read_file_content(struct File_Info* file_info){
	char* buffer = (char*)malloc(file_info->file_size + 1);

	fread(buffer, 1, file_info->file_size, file_info->file_pointer);

	buffer[file_info->file_size] = '\0';

	printf("%s", buffer);
	free(buffer);
	fclose(file_info->file_pointer);
	free(file_info);
}

void get_dir_files(char* dir_name){
	char directory[256] = "/home/Matixannder/Desktop/Projects/LearningC/WebserverC/src/";
	strcat(directory, dir_name);

	DIR* sub_dir = opendir(directory);
	
    if (sub_dir == NULL) {
        perror("Error al abrir el sub-directorio");
				return;
    }
	struct dirent *files;

	printf("Contenido del directorio %s\n\n", directory);
	while ((files = readdir(sub_dir)) != NULL) {
		if (strcmp(files->d_name, ".") == 0 || strcmp(files->d_name, "..") == 0) {
			continue;
		}
		printf("%s\n", files->d_name);
	}
	
	closedir(sub_dir);
}

void open_source_dir(){
    const char *ruta = "/home/Matixannder/Desktop/Projects/LearningC/WebserverC/src";

    struct dirent *entrada;

    DIR *directorio = opendir(ruta);

    if (directorio == NULL) {
        perror("Error al abrir el directorio");
				return;
    }

		while ((entrada = readdir(directorio)) != NULL) {
			if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
				continue;
			}

			if (strchr(entrada->d_name, '.') == NULL) {
				get_dir_files(entrada->d_name);
			}
		}
		closedir(directorio);
}

int main(){
	open_source_dir();


	//read_file_content(get_file_info("/home/Matixannder/Desktop/Projects/LearningC/WebserverC/src/index.html"));
	
	return 0;
}
