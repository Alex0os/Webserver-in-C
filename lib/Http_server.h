#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <stddef.h>

#include "routing.h"

typedef struct {
	int socket;
	int port;
	Hash_Table* routes;
} Http_server;;


int create_server(Http_server* new_server);
int handle_client(int host_socket);
char* get_request_header(int client_socket);
void send_response(int client_fd, char* buffer_content, int buffer_size);

#endif // HTTP_SERVER_H
