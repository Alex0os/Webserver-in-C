#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <stddef.h>

#include "routing.h"

typedef struct {
	int socket;
	int port;
	Hash_Table* routes;
} Http_server;


Http_server* create_server();
int handle_client(int host_socket);
char* request_uri(int client_socket);
void send_response(int client_fd, char* buffer_content, int buffer_size);

#endif // HTTP_SERVER_H
