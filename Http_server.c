#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stddef.h>

#include "lib/routing.h"

#define REQUEST_BUFFER_SIZE 16384 // 16 KB
#define PORT 8080

typedef struct {
	int socket;
	int port;
	Hash_Table* routes;
} Http_server;

Http_server* create_server();
int handle_client(int host_socket);
void send_response(int client_fd, char* buffer_content, int buffer_size);
void parse_request(int client_socket);
char* request_uri(int clinet_socket);
int get_request_line(char* request, char* buffer);
int get_request_header(char* request, char* buffer, int header_start);

Http_server* create_server(){
	Http_server* new_server = (Http_server*)malloc(sizeof(Http_server));

	new_server->socket = socket(AF_INET, SOCK_STREAM, 0);
	int option = 1;
	setsockopt(new_server->socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

	struct sockaddr_in host_addr;
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(PORT);
	host_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(new_server->socket, (struct sockaddr*)&host_addr, sizeof(host_addr)) < 0) {
		perror("A problem occurred in the binding process of the socket");
		return NULL;
	}

	if (listen(new_server->socket, SOMAXCONN) < 0) {
		perror("A problem ocurred while trying to start the listening process");
		return NULL;
	}

	printf("Socket initialized successfully for accepting connections\n");
	return new_server;
}


int handle_client(int host_socket){

	struct sockaddr_in client_addr;
	size_t client_addr_size = sizeof(client_addr);

	int client_socket = accept(host_socket, (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_size);

	if (client_socket < 0) {
		 perror("A problem happened while trying to connect to the client");
		 exit(EXIT_FAILURE);
	}
	return client_socket;
}

void send_response(int client_fd, char* buffer_content, int buffer_size){
	send(client_fd, (const void*)buffer_content, buffer_size, 0);
	close(client_fd);
}

char* request_uri(int client_socket){
	char request_buffer[REQUEST_BUFFER_SIZE];
	int bytes_recieved = recv(client_socket, request_buffer, REQUEST_BUFFER_SIZE, 0);
	request_buffer[bytes_recieved] = '\0';

	char line_buffer[100];
	char header_buffer[REQUEST_BUFFER_SIZE];
	
	int header_start = get_request_line(request_buffer, line_buffer);
	int body_start =  get_request_header(request_buffer, header_buffer, header_start);


	char* method = malloc(100);
	char* uri = malloc(100);
	char* version = malloc(100);

	sscanf(request_buffer, "%s %s %s", method, uri, version);
	free(method);
	free(version);
	return uri;
}


int get_request_line(char* request, char* buffer){
	int i = 0;
	
	 while (request[i] != '\n'){
		buffer[i] = request[i];
		i++;
	}

	buffer[i] = '\0';
	return i + 1;
}


int get_request_header(char* request, char* buffer, int header_start){
	int i = header_start;
	int j = 0;

	while (request[i] != '\n' || request[i + 2] != '\n'){
		buffer[j] = request[i];
		j++;
		i++;
	}

	buffer[j] = '\n';
	buffer[j + 1] = '\0';
	return i + 1;
}
