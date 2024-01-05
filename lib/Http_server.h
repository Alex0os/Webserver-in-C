#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <stddef.h>

#define BUFFER_SIZE 10000


typedef struct {
	int socket;
	int port;
} Http_server;;


int create_socket(Http_server* new_server);
void handle_client(int socket_fd, char* buffer, size_t buffer_size);

#endif // HTTP_SERVER_H
