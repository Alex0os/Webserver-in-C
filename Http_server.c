#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 10000
#define PORT 8080

typedef struct {
	int socket;
	int port;
} Http_server;;

void print_request(int client_socket);

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
	
	print_request(request_fd);


	send(request_fd, (const void*)buffer, buffer_size, 0);


	close(request_fd);
}

void print_request(int client_socket){
	char buffer[BUFFER_SIZE];
	int bytes_recieved = recv(client_socket, buffer, BUFFER_SIZE, 0);

	buffer[bytes_recieved] = '\0';

	printf("%s\n", buffer);
}


