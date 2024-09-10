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
	HashTable *routes;
} HttpServer;

typedef struct {
	char *line, *header;
	char body;
} Request;

HttpServer *create_server();
int handle_client(int host_socket);
void send_response(int client_fd, char *buffer_content, int buffer_size);
Request *accept_request(int client_socket);
char *request_uri(char *request_line);
int get_request_line(char *request, char *buffer);
int get_request_header(char *request, char *buffer, int header_start);

HttpServer *create_server()
{
	HttpServer *server = (HttpServer*)malloc(sizeof(HttpServer));

	server->socket = socket(AF_INET, SOCK_STREAM, 0);
	int option = 1;
	int options_status = setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR,
									&option, sizeof(option));
	if (options_status < 0) {
		perror("A problem occurred while trying to set the server's socket options");
		return NULL;
	}

	struct sockaddr_in host_addr;
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(PORT);
	host_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(server->socket, (struct sockaddr*)&host_addr, sizeof(host_addr)) < 0) {
		perror("A problem occurred in the binding process of the socket");
		return NULL;
	}

	if (listen(server->socket, SOMAXCONN) < 0) {
		perror("A problem ocurred while trying to start the listening process");
		return NULL;
	}

	printf("Socket initialized successfully for accepting connections\n");
	return server;
}


int handle_client(int host_socket)
{

	struct sockaddr_in client_addr;
	size_t client_addr_size = sizeof(client_addr);

	int client_socket = accept(host_socket, (struct sockaddr*)&client_addr,
							  (socklen_t*)&client_addr_size);

	if (client_socket < 0) {
		 perror("A problem happened while trying to connect to the client");
		 return -1;
	}
	return client_socket;
}

void send_response(int client_fd, char *buffer_content, int buffer_size)
{
	send(client_fd, (const void*)buffer_content, buffer_size, 0);
	close(client_fd);
}

char *request_uri(char *request_line)
{
	char method[100];
	char *uri = malloc(100);
	char version[100];

	sscanf(request_line, "%s %s %s", method, uri, version);
	return uri;
}

Request *accept_request(int client_socket)
{
	Request *request = (Request*)malloc(sizeof(Request));
	char body_buffer[REQUEST_BUFFER_SIZE], request_buffer[REQUEST_BUFFER_SIZE];

	request->line = (char*)malloc(100);
	request->header = (char*)malloc(REQUEST_BUFFER_SIZE);

	int bytes_recieved = recv(client_socket, request_buffer, REQUEST_BUFFER_SIZE, 0);
	request_buffer[bytes_recieved] = '\0';

	// \n\r -> Separates the first line with the header
	// \n\r\n\r -> Separates the headers from the body

	int header_start = get_request_line(request_buffer, request->line);
	int body_start =  get_request_header(request_buffer, request->header, header_start);

	return request;
}


int get_request_line(char *request, char *buffer)
{
	int i = 0;
	
	 while (request[i] != '\n'){
		buffer[i] = request[i];
		i++;
	}

	buffer[i] = '\0';
	return i + 1;
}


int get_request_header(char *request, char *buffer, int header_start)
{
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

void free_client(Request *client_request)
{
	free(client_request->line);
	free(client_request->header);
	free(client_request);
}

