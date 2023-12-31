#include <stdio.h>
#include <stdlib.h>

#include "lib/Http_server.h"

#define BUFFER_SIZE 10000

void parsing_request(char* buffer){
	char first_line[20];
	size_t i = 0;

	while (buffer[i] != '\n') {
		first_line[i] = buffer[i];
		i++;
	}

}

int main(){
	Http_server server;
	int socket_status = create_socket(&server);

	if (socket_status < 0){
		return 1;
	}

for (;;) {
		char* buffer = malloc(BUFFER_SIZE);

		handle_client(&server.socket, buffer, BUFFER_SIZE);
		printf("%s", buffer);

		parsing_request(buffer);

		free(buffer);
	}

	return 0;
}
