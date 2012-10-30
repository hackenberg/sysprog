#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>


/* === Constants === */

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
	uint8_t adress[RANGE];
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
	
	parse_args(argc, argv, &options);

	/* Create socket for client */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* Name the socket as agreed with server */
	adress.sin_family = AF_INET;

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
