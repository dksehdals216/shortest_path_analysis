/**
 * Dijkstra, Bellman-Ford, Floyd's Algorithm implementation against test case
 * data.
 * 21600397@handong.edu adominic022@gmail.com
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <limits.h>


#define MAX_STR_LEN 256

typedef struct Edge
{
    int source;
    int dest, weight;

}Edge;

typedef struct Graph
{
    int vert_n;
    int edge_n;

    struct Edge* edge;
}Graph;

char *replace_str(char *inp_str, char *target, char *new);

struct Graph* createGraph(int V, int E)
{
    Graph* graph = malloc(sizeof(Graph));
    graph->vert_n = V;
    graph->edge_n = E;
    graph->edge = malloc(sizeof(Edge[E]));
    return graph;
}

void printArr(int dist[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void BellmanFord(struct Graph* graph, int src)
{
    int V = graph->vert_n;
    int E = graph->edge_n;
    int dist[V];
 
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < V; i++)
        dist[i]   = INT_MAX;
    dist[src] = 0;
 
    // Step 2: Relax all edges |V| - 1 times. A simple shortest 
    // path from src to any other vertex can have at-most |V| - 1 
    // edges
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].source;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
 
    // Step 3: check for negative-weight cycles.  The above step 
    // guarantees shortest distances if graph doesn't contain 
    // negative weight cycle.  If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].source;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            printf("Graph contains negative weight cycle");
    }
 
    printArr(dist, V);
 
    return;
}

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
        buffer[n++] = c;
        if( c != '\t' && c != ' ' && c != '\n' && c != '\r')
        {
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

    //print location string
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

    //name tags for cities
    for(n = 0; n < c; n++)
    {
        //printf("%s\n", name[n]);
    }

    long (*adj_matrix)[counter] = malloc(sizeof * adj_matrix * counter);
    char delim[] = "\t\r\n\v\f";
    n = 0;
    k = 0;

    while(*replc_str)
    {
        if(isdigit(*replc_str))
        {
            long val = strtol(replc_str, &replc_str, 10);
            adj_matrix[n][k] = val;
            k++;
        }
        else
        {
            replc_str++;
        }
        if(k > 9)
        {
            k = 0;
            n++;
        }
    }


    for(n = 0; n < counter; n++)
    {
        for(k = 0; k < counter; k++)
        {
            printf("%ld ", adj_matrix[n][k]);
        }
            printf("\n");
    }


    Graph *llist_arr[counter];


    for(n = 0; n < counter; n++)
    {
        //freeLL(llist_arr[n]);
    }

 	free(buffer);
    //free(replc_str);
    free(adj_matrix);

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

}
/*
void freeLL(Graph *hd_ptr)
{
    Graph* tmp;
    while(hd_ptr != NULL)
    {
        tmp = hd_ptr;
        hd_ptr = hd_ptr->next;
        free(tmp);
    }
}

void append_Graph(Graph** hd_ptr, char in_index)
{
    Graph* new = (Graph*)malloc(sizeof(Graph));
    Graph* last = *hd_ptr;

    new->name_index = in_index;
    new->next = NULL;

    if(*hd_ptr == NULL)
    {
        *hd_ptr = new;
        return;
    }
    else
    {
        while(last->next != NULL)
        {
            last = last->next;
        }
    }
    last->next = new;
}
*/
