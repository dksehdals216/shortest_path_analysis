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
#include <sys/time.h>


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

void dijkstra(int counter, int (*graph)[counter], int n, int start_n)
{
 
    int cost[counter][counter];
    int dist[counter];
    int pred[counter];
    int vis[counter];
    int count;
    int min_dist;
    int next_n;
    int i,j;
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(graph[i][j] == 0)
            {
                cost[i][j] = MAX_LIMIT;
            }
            else
            {
                cost[i][j] = graph[i][j];
            }
        }
    }
    //initialize pred[],distance[] and visited[]
    for(i = 0; i < n; i++)
    {
        dist[i] = cost[start_n][i];
        pred[i] = start_n;
        vis[i] = 0;
    }
    
    dist[start_n] = 0;
    vis[start_n] = 1;
    count = 1;
    
    while(count < n-1)
    {
        min_dist = MAX_LIMIT;
        
        //check next node for min dist
        for(i = 0; i < n; i++)
        {
            if(dist[i] < min_dist &&! vis[i])
            {
                min_dist = dist[i];
                next_n = i;
            }
        }

        //Does Past exist?            
        vis[next_n] = 1;
        for(i = 0; i < n; i++)
        {
            if(!vis[i])
                if(min_dist + cost[next_n][i] < dist[i])
                {
                    dist[i] = min_dist + cost[next_n][i];
                    pred[i] = next_n;
                }
        }
        count++;
    }
 
    //print the path and distance of each node
    for(i = 0; i < n; i++)
    {
        if(i != start_n)
        {
            printf("%d  ", dist[i]);
        }
        else if(i == start_n)
        {
            printf("0  ");
        }
    }
    printf("\n");
}

void floyd(int counter, int (*graph)[counter])
{
    int dist[counter][counter];
    int i, j, k;

    for(i = 0; i < counter; i++)
    {
        for(j = 0; j < counter; j++)
        {
            dist[i][j] = graph[i][j];
        }
    }

    for(k = 0; k < counter; k++)
    {
        for(i = 0; i < counter; i++)
        {
            for(j = 0; j < counter; j++)
            {
                if(dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printf("\n\nFloyd Warshall Output: \n");
    for(i = 0; i < counter; i++)
    {
        for(j = 0; j < counter; j++)
        {
            if(dist[i][j] == MAX_LIMIT)
            {
                printf("%d ", MAX_LIMIT);
            }
            else
            {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

struct Graph* createGraph(int V, int E);
void BellmanFord(struct Graph* g, int source);
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

    int bufferlen = 0;
    struct timeval t1, t2;
    double elapsedT;

    
    fp = fopen ("data.txt", "r");
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
    buffer[n++] = '\0';


	counter = sqrt(counter);
    //printf("\n%s\n", buffer);

    n = 0;
    k = 0;
    c = 0;
    int (*adj_matrix)[counter] = malloc(sizeof * adj_matrix * counter);

    bufferlen = strlen(buffer);
    while(n < bufferlen)
    {
        if ((n < bufferlen - 4) && (buffer[n] == 'I') && (buffer[n+1] == 'N') && (buffer[n+2] == 'F'))
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

    //calculate edge:
    edge_n -= counter;
    edge_n /= 2;

    Graph* graph = createGraph(counter, edge_n);

    temp = 0;
    c = 0;

    //bellman ford out
    printf("Bellman Ford output: \n");
    gettimeofday(&t1, NULL);
    for(k = 0; k < counter; k++)
    {
        for(n = 0; n < counter; n++)
        {
            if(adj_matrix[k][n] < MAX_LIMIT)
            {
                graph->edge[c].source = k;
                graph->edge[c].dest = n;
                graph->edge[c].weight = adj_matrix[k][n];

                c++;
            }
        }
    }
    for(temp = 0; temp < counter; temp++)
    {
        BellmanFord(graph, temp);
    }
    gettimeofday(&t2, NULL);
    elapsedT = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedT += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("elapsed time: %lf microseconds\n", elapsedT);
    
    //dijkstra out
    gettimeofday(&t1, NULL);
    printf("\n\nDijkstra output: \n");
    for(temp = 0; temp < counter; temp++)
    {
        dijkstra(counter, adj_matrix, counter, temp);
    }
    gettimeofday(&t2, NULL);
    elapsedT = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedT += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("elapsed time: %lf microseconds\n", elapsedT);

    //floyd out
    gettimeofday(&t1, NULL);
    floyd(counter, adj_matrix);
    gettimeofday(&t2, NULL);
    elapsedT = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedT += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("elapsed time: %lf microseconds\n", elapsedT);


 	free(buffer);
    free(adj_matrix);
    free(graph);

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
        weight = graph->edge[i].weight;

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

