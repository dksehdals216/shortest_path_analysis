#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

void replace_str(char *inp_str, char *out_str);

static const char INF[] = "INF";

int main(int argc, char* argv[])
{
	FILE * fp;
	char *buffer;
	int f_size = 0;
	int counter = 0;
	int c;
	int n = 0;

    if (argc != 2)
    {
        printf ("Usage: ./scc filename\n");
        return -1;
    }

    fp = fopen (argv[1], "r");
    if (fp == NULL)
    {
        printf("failed to open file");
        return 0;
    }

    fseek (fp, 0L, SEEK_END);
    f_size = ftell(fp);
    fseek (fp, 0L, SEEK_SET); //or use rewind(fp);


    buffer = (char *) malloc(f_size);
	if (!buffer)
	{
		printf("Failed to allocate buffer!!\n");
	}

    while ((c = fgetc(fp)) != EOF)
    {       
        if( c != '\t' && c != ' ' && c != '\n' && c != '\r')
        {
            buffer[n++] = c;
            if(!isalpha(c))
            {
            	counter++;
            }
        }
    }


	counter = sqrt(counter);
 	
 	char name[counter];
 	for(n = 0; n < counter; n++)
 	{
 		//printf("%d\n", buffer[n]);
 	}

 	free(buffer);
}

void replace_str(char *inp_str, char *	out_str)
{
	int i = 0;
	int cnt = 0;
	int inp_len = strlen(inp_str);
	int out_len = strlen(out_str);
}
