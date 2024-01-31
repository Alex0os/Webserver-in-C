#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "lib/routing.h"
#include "lib/urls.h"

#define BUFFER_SIZE 10000
#define PORT 8080

typedef struct {
	int socket;
	int port;
	Hash_Table* routes;
} Http_server;;


int create_server(Http_server* new_server){

	new_server->socket = socket(AF_INET, SOCK_STREAM, 0);
	int option = 1;
	setsockopt(new_server->socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

	struct sockaddr_in host_addr;
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(PORT);
	host_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(new_server->socket, (struct sockaddr*)&host_addr, sizeof(host_addr)) < 0) {
		perror("A problem occurred in the binding process of the socket");
		return -1;
	}

	if (listen(new_server->socket, SOMAXCONN) < 0) {
		perror("A problem ocurred while trying to start the listening process");
		return -1;
	}

	/*This is the function used to create the server, and due to the fact that we're looking
	 * for a change in the internal functioning of the server itself, then first how are we
	 * gonna change and what are we gonna change
	 *
	 * First of all, it is supposed that we're adding some characteristics to the hash table, first,
	 * we're gonna add the process to add the routes related to resources in the system
	 */

	new_server->routes = defining_routes();

	printf("Socket initialized successfully for accepting connections\n");
	return 0;
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

char* get_request_header(int client_socket){
	char buffer[BUFFER_SIZE];
	int bytes_recieved = recv(client_socket, buffer, BUFFER_SIZE, 0);

	buffer[bytes_recieved] = '\0';
	char* method = malloc(100);
	char* uri = malloc(100);;
	char* version = malloc(100);;

	sscanf(buffer, "%s %s %s", method, uri, version);
	free(method);
	free(version);
	return uri;
}


