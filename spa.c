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


#define MAX_STR_LEN 256
#define MAX_LIMIT 9999

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


struct Graph* createGraph(int V, int E);
void BellmanFord(struct Graph* graph, int source);
void out_res(int dist[], int n);
void print_name(int counter, char name[][MAX_STR_LEN]);

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
    int temp = 0;
    int edge_n = 0;


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
    //printf("\n%s\n", buffer);

    n = 0;
    k = 0;
    c = 0;
    int (*adj_matrix)[counter] = malloc(sizeof * adj_matrix * counter);

    while(n < strlen(buffer))
    {
        if ((n < strlen(buffer) - 4) && (buffer[n] == 'I') && (buffer[n+1] == 'N') && (buffer[n+2] == 'F'))
        {
            adj_matrix[c][k] = MAX_LIMIT;
            n+=3;
            k++;
        }
        else if (isdigit(buffer[n]))
        {
            temp = 0;
            edge_n++;
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

    /*
    for(n = 0; n < counter; n++)
    {
        for(k = 0; k < counter; k++)
        {
            printf("%d ", adj_matrix[n][k]);
        }
            printf("\n");
    }
    */

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
    
    //calculate edge:
    edge_n -= counter;
    edge_n /= 2;

    //printf("Edgen: %d\n", edge_n);

    Graph* graph = createGraph(counter, edge_n);
    //print_name(counter, name);


    c = 0;
    temp = 0;
   /* 
    for(temp = 0; temp < counter; temp++)
    {*/
        for(k = 0; k < counter; k++)
        {
            for(n = 0; n < counter; n++)
            {
                if(adj_matrix[k][n] < 9999)
                {
                    //printf("source: %d dest: %d weight: %d\n", k, n, adj_matrix[k][n]);
                    graph->edge[c].source = k;
                    graph->edge[c].dest = n;
                    graph->edge[c].weight = adj_matrix[k][n];

                    c++;
                }
            }
        }

        BellmanFord(graph, temp);
    //}
    


 	free(buffer);
    free(adj_matrix);

}

struct Graph* createGraph(int V, int E)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vert_n = V;
    graph->edge_n = E;
    graph->edge = (Edge*)malloc(graph->edge_n * sizeof(Edge));
    return graph;
}

void BellmanFord(struct Graph* graph, int source)
{
    int V = graph->vert_n;
    int E = graph->edge_n;
    int dist_src[V];
    int past_[V];
    int i, j, u, v, weight;

    //init single source 
    for(i = 0; i < V; i++)
    {
        dist_src[i] = MAX_LIMIT;
        past_[i] = 0;
    }
    dist_src[source] = 0;

    //relax
    for(i = 0; i < V-1; i++)
    {
        for(j = 0; j < E; j++)
        {
            u = graph->edge[j].source;
            v = graph->edge[j].dest;
            weight = graph->edge[j].weight;

            if ((dist_src[u] != MAX_LIMIT) && (dist_src[u] + weight < dist_src[v]))
            {
                dist_src[v] = dist_src[u] + weight;
                past_[v] = u;
            }
        }
    }

    //neg cycle check
    for(i = 0; i < E; i++)
    {
        u = graph->edge[i].source;
        v = graph->edge[i].dest;
        weight = graph->edge[j].weight;

        if (dist_src[u] != MAX_LIMIT && dist_src[u] + weight < dist_src[v])
        {
            printf("neg cycle\n");
        }
    }

    out_res(dist_src, V);
}
 
void out_res(int dist[], int n)
{
    int i;
 
    for (i = 0; i < n; ++i){
        printf("%d  ", dist[i]);
    }
    printf("\n");
}

void print_name(int counter, char name[][MAX_STR_LEN])
{
    int i;

    for(i = 0; i < counter; i++)
    {
        printf("%s", name[i]);
    }
    printf("\n");
}
