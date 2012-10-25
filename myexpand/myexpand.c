#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ISDIGIT differs from isdigit, as follows:
   - Its arg may be any int or unsigned int; it need not be an unsigned char
     or EOF.
   - It's typically faster.
   POSIX says that only '0' through '9' are digits.  Prefer ISDIGIT to
   isdigit unless it's important to use the locale's definition
   of 'digit' even when the host does not conform to POSIX.  */
#define ISDIGIT(c) ((unsigned int) (c) - '0' <= 9)

static const char* usage = "usage: myexpand [-t tabstop] [file...]";
static unsigned int tabstop = 8;
static unsigned int pos = 0;

/* Null-terminated array of input filenames. */
static char **file_list;

static char const shortopts[] = "t:";

/**
 * @brief expands a list of files
 * @details calls the expand function for a list of files instead of reading
 * from stdin.
 * @return 0 on success; otherwise non-zero
 */
static void expand_files(void)
{
    //FILE *fp = nextFile(NULL);
    FILE *fp;
    while(*file_list != NULL)
    {
        fp = fopen(*file_list++, "r");
        if(fp == NULL)
        {
	    fprintf(stderr, strerror(errno));

            // TODO: errorhandling
            printf("could not open file: %s", *file_list);
        }
        else
        {
            char c;
            while((c = fgetc(fp)) != EOF)
            {
                if(c == '\t')
                {
                    assert(tabstop > 0);
                    int p = tabstop * ((pos / tabstop) + 1);
                    while(pos < p)
                    {
                        printf(" ");
                        pos++;
                    }
                }
                else
                {
                    printf("%c", c);
                    c == '\n' ? pos = 0 : pos++;
                }
            }
        }
        (void) fclose(fp);
    }
    return;
}

/**
 * @brief expands stdin
 * @details calls the expand function for stdin
 * @return 0 on success; otherwise non-zero
 */
static void expand_stdin(void)
{
    char *buffer = malloc(sizeof (char));
    char *tmp;
    if(buffer == 0)
    {
        // TODO: errorhandling
        printf("Error allocating memory!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        int i = 0;
        char c;
        while((c = getchar()) != EOF)
        {
            if(c == '\t')
            {
                assert(tabstop > 0);
                int p = tabstop * ((pos / tabstop) + 1); // maybe as macro?
                buffer = tmp;
                while(pos < p)
                {
                    tmp = realloc(buffer, (i+1)*sizeof(char));
                    if(tmp == 0)
                    {
                        // TODO: errorhandling
                        free(buffer);
                        printf("Error allocating memory!\n");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        buffer = tmp;
                        buffer[i] = ' ';
                        pos++;
                        i++;
                    }
                }
            }
            else
            {
                tmp = realloc(buffer, (i+1)*sizeof(char));
                if(tmp == 0)
                {
                    // TODO: errorhandling
                    free(buffer);
                    printf("Error allocating memory!\n");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    buffer = tmp;
                    buffer[i] = c;
                    c == '\n' ? pos = 0 : pos++;
                    i++;
                }
            }
        }
        tmp = realloc(buffer, (i)*sizeof(char));
        if(tmp == 0)
        {
            // TODO: errorhandling
            free(buffer);
            printf("Error allocating memory!\n");
            exit(EXIT_FAILURE);
        }
        buffer[i] = '\0';
        printf("%s", buffer);
        free(buffer);
    }
    return;
}

/**
 * @brief Program entry point
 * @details reads options and arguments with getopt and calls the appropriate
 * expand function.
 *
 * @param argc The argument counter
 * @param argv The argument vector
 * @return 0 on success; otherwise non-zero
 */
int main(int argc, char **argv)
{
    int c;
    while((c = getopt(argc, argv, shortopts)) != -1)
    {
        switch(c)
        {
            case 't':
                if(ISDIGIT(*optarg))
                {
                    tabstop = strtol(optarg, NULL, 0);
                    if(tabstop == 0)
                    {
                        // TODO: errorhandling
                        printf("tabstop cannot be 0");
                        return 1;
                    }
                }
                else
                {
                    // TODO: errorhandling
                    printf("NaN");
                    return 1;
                }
                break;

            case ':':
                // TODO: errorhandling
                printf("case ':'");
                return 1;

            case '?':
                // TODO: errorhandling
                printf("case '?'");
                return 1;

            default:
                assert(0);
        }
    }

    if(optind < argc)
    {
        file_list = &argv[optind];
        expand_files();
    }
    else
        expand_stdin();

    return 0;
}
