#include <stdio.h>
#include <stdlib.h>

#include "lib/Http_server.h"

#define BUFFER_SIZE 10000



int main(void)
{

	Http_server http_server;

	if (create_socket(&http_server) < 0){
		exit(EXIT_FAILURE);
	}

	char buffer[BUFFER_SIZE];

	for (;;) {
		handle_client(http_server.socket, buffer, BUFFER_SIZE);

		printf("%s\n", buffer);
	}

	return EXIT_SUCCESS;
}
