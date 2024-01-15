#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct Header_Info {
	char* header_content;
	size_t header_size;
};

// Seria mas simple solamente tomar la función que abre los archivos y desde hay definir obtener la extensión
struct Header_Info* definir_tipo_y_subtipo(char* extention);
char* file_content(FILE* file, int file_size);
int file_size(FILE* file);

struct Header_Info* definir_tipo_y_subtipo(char* extention){
	struct Header_Info* header = (struct Header_Info*)malloc(sizeof(struct Header_Info));

	if (strcmp(extention, ".html") == 0){
		header->header_content = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
		header->header_size = strlen(header->header_content);
		return header;
	}
	else if (strcmp(extention, ".css") == 0){
		header->header_content = "HTTP/1.1 200 OK\r\nContent-Type: text/css\r\n\r\n";
		header->header_size = strlen(header->header_content);
		return header;
	}
	else if (strcmp(extention, ".js") == 0){
		header->header_content = "HTTP/1.1 200 OK\r\nContent-Type: text/js\r\n\r\n";
		header->header_size = strlen(header->header_content);
		return header;
	}
	else if (strcmp(extention, ".png") == 0){
		header->header_content = "HTTP/1.1 200 OK\r\nContent-Type: image/png\r\n\r\n";
		header->header_size = strlen(header->header_content);
		return header;
	}
	else if (strcmp(extention, ".jpeg") == 0){
		header->header_content = "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n";
		header->header_size = strlen(header->header_content);
		return header;
	}
	free(header);
	return NULL;
}

int file_size(FILE* file){
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


