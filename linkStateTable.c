#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <malloc.h>

int minDistance(int dist[], bool visit[],int V){
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++){
        if (visit[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    }

    return min_index;
}

void printRoutingTable(int prev[],int V){

    printf("\nDestination\tNextNode\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, prev[i]);
}

void genRoutingTable(int **graph, int src,int V)
{
    // The output array - dist[i] will hold the shortest distance from src to i
	int dist[V];
	// prev array contain the prev node from where the node is reached from source
	int prev[V];

	//visited array is set to true if vertex i is included in the spanning tree
	bool visited[V];

	// Initialize all distances as INFINITE and visited[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, visited[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;
	//previous node of source is also itself
    prev[src]=0;

	// Find shortest path for all vertices from source
	for (int c = 0; c < V-1; c++){
        // Pick the minimum distance vertex from the set of vertices not yet visited
        //u is always equal to src in first iteration.
        int u = minDistance(dist, visited,V);

        // Mark the picked vertex as visited
        visited[u] = true;

        // Update distance value of the adjacent vertices of the picked/visted vertex.
        for (int v = 0; v < V; v++){
            // Update dist[v] only if is not in visited,
            // there is an edge from u to v,
            // and total weight of path from src to v through u is smaller than current value of dist[v]
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
	}


    //Now maipulate the prev[] array which contain the just previous node for the destination

    //Node with previous node is source node will always have the nextnode as itself
    for(int i=0;i<V;++i){
        if(prev[i]==src){
            prev[i]=i;
        }
    }

    //manipulate the prev array to have next node value to reach the destination from source
	for(int i=1;i<V;++i){
	    //change the prev[i] till it find a node which is directly reachable form source
	    while(graph[src][prev[i]]==0){
	        //since the prev[i] node is not directly reachable to source
	        //so set the prev[i] to the previous node of its previous node
            prev[i]=prev[prev[i]];
        }
    }

    //display the routing table
	printRoutingTable(prev,V);

}

int main(){

    int n;
    printf("\nEnter the no. of nodes : ");
    scanf("%d",&n);

    //dynamic memory allocation since the no. of node is unknown
    int **graph;
    /* allocate the array */
    graph = malloc(n* sizeof *graph);
    for (int i=0; i<n; i++){
        graph[i] = malloc(n * sizeof *graph[i]);
    }

    //take input in the form of adjacency matrix
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            scanf("%d",&graph[i][j]);
        }
    }

    //display the adjacency matrix entered
    printf("\nAdjacency matrix :\n");
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            printf(" %d",graph[i][j]);
        }
        printf("\n");
    }
    int src;
    printf("\nEnter the source ( any out of 0 to n-1 ) : ");
    scanf("%d",&src);

    //call the dijkstra algorithm
	genRoutingTable(graph, src, n);

	return 0;
}

