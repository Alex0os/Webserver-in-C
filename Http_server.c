#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

typedef struct {
	int socket;
	int port;
} Http_server;;

char* file_content(FILE* file, int file_size);
int file_size(FILE* file);

int create_socket(Http_server* new_server){

	new_server -> socket = socket(AF_INET, SOCK_STREAM, 0);
	int option = 1;
	setsockopt(new_server -> socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

	struct sockaddr_in host_addr;
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(PORT);
	host_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(new_server -> socket, (struct sockaddr*)&host_addr, sizeof(host_addr)) < 0) {
		perror("A problem occurred in the binding process of the socket");
		return -1;
	}

	if (listen(new_server -> socket, SOMAXCONN) < 0) {
		perror("A problem ocurred while trying to start the listening process");
		return -1;
	}

	printf("Socket initialized successfully for accepting connections\n");
	return 0;
}

void handle_client(int socket_fd, char* buffer, size_t buffer_size){

	struct sockaddr_in client_addr;
	size_t client_addr_size = sizeof(client_addr);

	ssize_t request_fd = accept(socket_fd, (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_size);

	if (request_fd < 0) {
		 perror("A problem happened while trying to connect to the client");
		 exit(EXIT_FAILURE);
	}
	
	recv(request_fd, buffer, buffer_size, 0);

	FILE* html_file = fopen("src/index.html", "r");
	int html_size = file_size(html_file);
	char* html_content = file_content(html_file, html_size);

	char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n\r\n\r\n<h1>Hello world</h1>";
	char full_response[html_size + strlen(response)];

	strcpy(full_response, response);
	strcat(full_response, html_content);

	send(request_fd, full_response, strlen(full_response), 0);

	

	free(html_file);
	free(html_content);
	close(request_fd);
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


