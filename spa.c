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

struct Graph* createGraph(int V, int E)
{
    Graph* graph = malloc(sizeof(Graph));
    graph->vert_n = V;
    graph->edge_n = E;
    graph->edge = malloc(sizeof(Edge[E]));
    return graph;
}

void printArr(int dist[], int n);
void BellmanFord(struct Graph* graph, int src);

int main(int argc, char* argv[])
{
	FILE * fp;
	char *buffer;
    char *replc_str = NULL;

	int f_size = 0;
	int counter = 0;
	int c;
	int n = 0;
    int k = 0;


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


	counter = sqrt(counter);
    printf("\n%s\n", buffer);

    printf("\n%s\n", buffer);

    n = 0;
    k = 0;
    c = 0;
    int temp = 0;
    int (*adj_matrix)[counter] = malloc(sizeof * adj_matrix * counter);

    while(n < strlen(buffer))
    {
        if ((n < strlen(buffer) - 4) && (buffer[n] == 'I') && (buffer[n+1] == 'N') && (buffer[n+2] == 'F'))
        {
            adj_matrix[c][k] = 9999;
            n+=3;
            k++;
        }
        else if (isdigit(buffer[n]))
        {
            temp = 0;
            while(isdigit(buffer[n+temp]))
            {
                adj_matrix[c][k] = adj_matrix[c][k] * 10 + (buffer[n+temp] - '0');
                temp++;
            }
            if(temp > 1)
            {
                n+=temp;
                k++;
            }
            else
            {
                adj_matrix[c][k] = buffer[n] - '0';
                k++;
                n++;
            }
        }
        else
        {
            n++;
        }
        
        if(k > 9)
        {
            k = 0;
            c++;
        }
    }

    for(n = 0; n < counter; n++)
    {
        for(k = 0; k < counter; k++)
        {
            printf("%d ", adj_matrix[n][k]);
        }
            printf("\n");
    }

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
    k = 0;
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

    for(n = 0; n < counter; n++)
    {
        for(k = 0; k < counter; k++)
        {
            printf("%ld ", adj_matrix[n][k]);
        }
            printf("\n");
    }

 	free(buffer);
    free(adj_matrix);

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


