#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#define MAXLENGTH 80

// TODO: check guidelines

/* char pointer that points to the string literal ("usage: ...") */
const char* usage = "usage: myexpand [-t tabstop] [file...]";

//char[] expand(char *c);

int main(int argc, char **argv)
{
    int tabstop = 8;
    int pos = 0; /* position innerhalb einer Zeile der Datei */
    char argshift = 0; /* zählt wie viele Argumente verwendet wurden */

    char c;
    while((c = getopt(argc,argv,":t:")) != -1)
    {
        switch(c)
        {
            case 't':
                if(isdigit((int) *optarg))
                {
                    tabstop = atoi(optarg); /* atoi() ist verboten */
                    argshift += 2; /* +2 bei optionen mit verpfl. argumenten */
                }
                else
                {
                    fprintf(stderr, usage);
                    return(-1);
                }
                break;

            case ':': /* nur wenn kein Dateiname und kein Argument vorliegt */
                fprintf(stderr, usage);
                return(-1);

            case '?':
                fprintf(stderr, usage);
                return(-1);
        }
    }

    if(argv[optind] == 0) /* kein Dateiname angegeben */
    {
        /* von stdin einlesen */
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
                else if(x == '\n')
                {
                    printf("%c", x);
                    pos = 0;
                }
                else
                {
                    printf("%c", x);
                    pos++;
                }
            }
        }
    }
    else /* einer oder mehrere Dateinamen wurden angegeben */
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
                    else if(x == '\n')
                    {
                        printf("%c", x);
                        pos = 0;
                    }
                    else
                    {
                        printf("%c",x);
                        pos++;
                    }
                }
                fclose(fp);
            }
        }
    }
    return 0;
}

/*
char[] expand(char *c)
{
    int pos = 0;  position innerhalb einer Zeile der Datei 

    char x;
    while((x = fgetc
    if(x == '\t')
    {
        int p = tabstop * ((pos / tabstop) + 1);
        while(pos++ < p)  postincrement!!! 
        {
            printf(" ");
        }
    }
    else if(x == '\n')
    {
        printf("%c", x);
        pos = 0;
    }
    else
    {
        printf("%c",x);
        pos++;
    }
}
*/
