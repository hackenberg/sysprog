#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLENGTH 80

/* TODO: check guidelines */

/* char pointer that points to the string literal ("usage: ...") */
const char* usage = "usage: myexpand [-t tabstop] [file...]";

char* strexp(char*, int);

int main(int argc, char **argv)
{
    unsigned int tabstop = 8;
    int pos = 0;
    char argshift = 0; /* counts how many options have been used */

    char c;
    while((c = getopt(argc,argv,":t:")) != -1)
    {
        switch(c)
        {
            case 't':
                if(isdigit((int) *optarg)) /* sanity check of the input */
                {
                    tabstop = atoi(optarg); /* atoi() is forbidden */
                    argshift += 2; /* +2 if theres an option with a mandatory arg */
                }
                else
                {
                    fprintf(stderr, usage);
                    return(-1);
                }
                break;

            case ':': /* only if there's no option AND no filename */
                fprintf(stderr, usage);
                return(-1);

            case '?':
                fprintf(stderr, usage);
                return(-1);
        }
    }

    if(argv[optind] == 0) /* no filename specified */
    {
        /* read from stdin */
        char* str;
        while(fgets(str,MAXLENGTH,stdin) != 0)
        {
            char x;
            while((x = *str++) != '\0')
            {
                if(x == '\t')
                {
                    int p = tabstop * ((pos / tabstop) + 1);
                    while(pos++ < p) /* postincrement!!! */
                    {
                        printf(" ");
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
    else /* one or more filename(s) specified */
    {
        argc -= argshift;
        argv += argshift;
        while(--argc > 0)
        {
            FILE *fp = fopen(*++argv,"r");

            /* fopen returns 0, the NULL pointer, on failure */
            if(fp == 0)
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
                        while(pos++ < p) /* postincrement!!! */
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

char* strexp(char* str, int tabstop)
{
    int pos = 0;
    char* out;
    //char out[strlen(str)];

    char x;
    while((x = *str++) != '\0')
    //while((*out++ = *str++) != '\0')
    {
        if(x == '\t')
        {
            int p = tabstop * ((pos / tabstop) + 1);
            while(pos++ < p) /* postincrement!!! */
            {
                *out++ = ' ';
                pos++;
            }
        }
        else if(x == '\n')
        {
            *out++ = x;
        }
        else
        {
            *out++ = x;
            pos++;
        }
    }
    return out;
}
