#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/* === Constants === */

#define BUFFER_BYTES (2)

/* === Global Variables === */

static int sockfd = -1;

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char **argv)
{
	int portno;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[BUFFER_BYTES];
	char *endptr;

	if(argc < 3) {
		(void) fprintf(stderr, "usage: %s hostname port", argv[0]);
		exit(1);
	}

	portno = strtol(argv[2], &endptr, 10);
	if(endptr != NULL) {
		(void) fprintf(stderr, "ERROR, no such port");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		error("ERROR opening socket");
	}
	server = gethostbyname(argv[1]);
	if(server == NULL) {
		(void) fprintf(stderr, "ERROR, no such host");
		exit(1);
	}

	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr_list[0], (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("ERROR connecting");
	}

	return 0;
}
