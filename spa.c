#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>


#define MAX_STR_LEN 256

char *replace_str(char *inp_str, char *target, char *new);


int main(int argc, char* argv[])
{
	FILE * fp;
	char *buffer;
    char *replc_str = NULL;
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


    char ch[] = "INF";
    char t[] = "-1";
	counter = sqrt(counter);

    replc_str = replace_str(buffer, ch, t);
    printf("\n%s\n", replc_str);

    char name[counter][MAX_STR_LEN];
    for(n = 0; n < counter; n++)
    {
        memset(name[n], '\0', sizeof(name[n]));
    }

    n = 0;
    while(1)
    { 
        if(isdigit(buffer[n]))
        {
           buffer[n] = '\0'; 
           break;
        }
        n++;       
    }
    printf("%s\n\n", buffer);

    c = 0;
    int k = 0;
    for(n = 1; n < strlen(buffer); n++)
    {
        if(isupper(buffer[n]))
        {
            strncpy(name[c], buffer + k, n - k);
            k = n;
            c++;
        }
    }
    for(n = 0; n < counter; n++)
    {

        printf("%s\n", name[n]);
    }

    for(n = 0; n < counter; n++)
    {
    }

 	free(buffer);
    free(replc_str);
}

char *replace_str(char *inp_str, char *target, char *new)
{
	int i = 0;
	int cnt = 0;
	int tok_rep = strlen(new);
	int tok_len = strlen(target);
    char *out_str;
    
    for(i = 0; inp_str[i] != '\0'; i++)
    {
        if(strstr(&inp_str[i], target) == &inp_str[i])
        {
            cnt++;
            i+= tok_len - 1;
        }
    }

    out_str = (char *)malloc(i + cnt * (tok_rep - tok_len));

    i = 0;
    while(*inp_str)
    {
        if(strstr(inp_str, target) == inp_str)
        {
            strcpy(&out_str[i], new);
            i += tok_rep;
            inp_str += tok_len;
        }
        else
        {
            out_str[i++] = *inp_str++;
        }
    }
    out_str[i] = '\0';
    return out_str;

>>>>>>> 9fc2b747716ee73bcfc4a0af550628fb1cf00657
}

