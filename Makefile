COMP = gcc
FLAGS = -o

create_server: 
	$(COMP) $(FLAGS) bin/Server Http_server.c utils.c 
