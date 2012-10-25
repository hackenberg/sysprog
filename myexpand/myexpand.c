#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLENGTH 80 /* maximum length of an input line from stdin */

/* ISDIGIT differs from isdigit, as follows:
   - Its arg may be any int or unsigned int; it need not be an unsigned char
     or EOF.
   - It's typically faster.
   POSIX says that only '0' through '9' are digits.  Prefer ISDIGIT to
   isdigit unless it's important to use the locale's definition
   of 'digit' even when the host does not conform to POSIX.  */
#define ISDIGIT(c) ((unsigned int) (c) - '0' <= 9)

/* TODO: headerfile erstellen mit z.b. define Maxlength */

static const char* usage = "usage: myexpand [-t tabstop] [file...]";
static unsigned int tabstop = 8;

/* Null-terminated array of input filenames. */
static char **file_list;

/* Default for 'file_list' if no files are given on the command line. */
static char *stdin_argv[] =
{
    (char *) "-", NULL
};

static char const shortopts[] = "t:";

/*
static FILE* nextFile(FILE *fp)
{
}
    

static void expand(void)
{
}
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
                        return 0;
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

    file_list = (optind < argc ? &argv[optind] : stdin_argv);

    while(*file_list != NULL)
    {
        printf("%s\n", *file_list++);
    }

    return 0;
}
