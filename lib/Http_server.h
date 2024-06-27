#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <stddef.h>

#include "routing.h"

typedef struct {
	int socket;
	int port;
	Hash_Table* routes;
} Http_server;

typedef struct{
	char* line;
	char* header;
	char body;
} Request;


Http_server* create_server();
int handle_client(int host_socket);
char* request_uri(char* request_line);
void send_response(int client_fd, char* buffer_content, int buffer_size);
Request* accept_request(int client_socket);
void free_client(Request* client_request);

#endif // HTTP_SERVER_H
