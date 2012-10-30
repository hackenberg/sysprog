#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


/* === Constants === */

#define MAX_TRIES (35)
#define SLOTS (5)
#define COLORS (8)

#define RANGE (32)


/* === Global Variables === */

/* Name of the program */
static const char *progname = "client"; /* default name */

/* File descriptor for server socket */
static int sockfd = -1;

/* File descriptor for connection socket */
//static int connfd = -1;

/* === Type Definitions === */

struct opts {
	long int portno;
	char address[RANGE];
};


/* === Prototypes === */

/**
 * @brief Parse command line options
 * @param argc The argument counter
 * @param argv The argument vector
 * @param options Struct where parsed arguments are stored
 */
static void parse_args(int argc, char **argv, struct opts *options);


int main(int argc, char **argv)
{
	struct opts options;
	int len, rc;
	struct sockaddr_in address;
	char result;
	char guess[SLOTS];
	
	parse_args(argc, argv, &options);

	/* Create socket for client */
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) {
		// TODO: errorhandling
		return 1;
	}

	/* Name the socket as agreed with server */
	address.sin_family = AF_INET;
	inet_pton(AF_INET, options.address, &address.sin_addr);
	address.sin_port = htons(options.portno);

	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1) {
		// TODO: errorhandling
		return 1;
	}

	int i;
	for(i = 0; i < SLOTS; i++)
	{
		/* Read and write via sockfd */
		rc = write(sockfd, &guess[i], 1);
		if(rc == -1) break;

		//read(sockfd, &guess, 1);
	}
	close(sockfd);

	return 0;
}

static void parse_args(int argc, char **argv, struct opts *options)
{
	char *addr_arg;
	char *port_arg;
	char *endptr;

	if(argc > 0) {
		progname = argv[0];
	}
	if(argc < 3) {
		// TODO: errorhandling
	}
	addr_arg = argv[1];
	port_arg = argv[2];

	options->portno = strtol(port_arg, &endptr, 10);
}
