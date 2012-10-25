#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLENGTH 80 /* maximum length of an input line from stdin */

/* TODO: headerfile erstellen mit z.b. define Maxlength */

const char* usage = "usage: myexpand [-t tabstop] [file...]";

int main(int argc, char **argv)
{
    unsigned int tabstop = 8;
    unsigned int pos = 0;
    char argshift = 0; /* counts how many options and/or args have been used */

    char c;
    while((c = getopt(argc,argv,":t:")) != -1) /* parse input */
    {
        switch(c)
        {
            case 't':
                if(isdigit((int) *optarg)) /* sanity check of the input */
                {
                    tabstop = strtol(optarg,NULL,0);
                    argshift += 2; /* option and argument --> 2 fields in argv */
                }
                else
                {
                    fprintf(stderr, usage);
                    return(1);
                }
                break;
            case ':': /* only if there's no option AND no filename */
                fprintf(stderr, usage);
                return(1);
            case '?':
                fprintf(stderr, usage);
                return(1);
            default:
                assert(0);
        }
    }

    if(argv[optind] == 0) /* if no filename specified --> read from stdin */
    {
        char* str;
        while(fgets(str,MAXLENGTH,stdin) != 0)
        {
            char x;
            while((x = *str++) != '\0')
            {
                if(x == '\t')
                {
                    int p = tabstop * ((pos / tabstop) + 1);
                    while(pos < p)
                    {
                        printf(" ");
                        pos++; /* cannot be pulled in to the loop head */
                    }
                }
                else
                {
                    printf("%c", x);
                    (x == '\n') ? pos = 0 : pos++;
                }
            }
        }
    }
    else /* --> read file(s) */
    {
        argc -= argshift;
        argv += argshift;
        while(--argc > 0)
        {
            FILE *fp = fopen(*++argv,"r");
            if(fp == 0) /* NULL pointer --> failure */
            {
                printf("Could not open file: \"%s\"", *argv);
            }
            else
            {
                char x;
                while((x = fgetc(fp)) != EOF)
                {
                    if(x == '\t')
                    {
                        int p = tabstop * ((pos / tabstop) + 1);
                        while(pos++ < p)
                        {
                            printf(" ");
                        }
                    }
                    else
                    {
                        printf("%c",x);
                        (x == '\n') ? pos = 0 : pos++;
                    }
                }
                fclose(fp);
            }
        }
    }
    return 0;
}
