#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *changewords_1 (char *sentence, char *find, char *replace)
{
    char *dest = malloc (strlen(sentence)-strlen(find)+strlen(replace)+1);
    char *destptr = dest;

    *dest = 0;

    while (*sentence)
    {
        if (!strncmp (sentence, find, strlen(find)))
        {
            strcat (destptr, replace);
            sentence += strlen(find);
            destptr += strlen(replace);
        } else
        {
            *destptr = *sentence;
            destptr++;
            sentence++;
        }
    }
    *destptr = 0;
    return dest;
}

char *changewords_2 (char *sentence, char *find, char *replace)
{
    char *dest = malloc (strlen(sentence)-strlen(find)+strlen(replace)+1);
    char *destptr = dest;

    *dest = 0;

    while (*sentence)
    {
        if (!strncmp (sentence, find, strlen(find)) &&
            (sentence[strlen(find)] == 0 || sentence[strlen(find)] == ' '))
        {
            strcat (destptr, replace);
            sentence += strlen(find);
            destptr += strlen(replace);
        } else
        {
            while (*sentence && *sentence != ' ')
            {
                *destptr = *sentence;
                destptr++;
                sentence++;
            }
            while (*sentence == ' ')
            {
                *destptr = *sentence;
                destptr++;
                sentence++;
            }
        }
    }
    *destptr = 0;
    return dest;
}

char *changewords_3 (char *sentence, char *find, char *replace)
{
    char *dest = malloc (strlen(sentence)-strlen(find)+strlen(replace)+1);
    char *ptr;

    strcpy (dest, sentence);

    ptr = strstr (dest, find);
    if (ptr)
    {
        memmove (ptr+strlen(replace), ptr+strlen(find), strlen(ptr+strlen(find))+1);
        strncpy (ptr, replace, strlen(replace));
    }

    return dest;
}


int main (void)
{
    char *result;

    result = changewords_1 ("Hello I'm Number One","Number","Index");
    printf ("[%s]\n", result);
    free (result);

    result = changewords_2 ("Here Is The One     Onerous Number One ...","One","Four");
    printf ("[%s]\n", result);
    free (result);

    result = changewords_3 ("Here Is Number One Again","One","Fourty-Five Hundred");
    printf ("[%s]\n", result);
    free (result);

    return 0;
}