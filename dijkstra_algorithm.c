/*
Name: dijkstra_algorithm.c
Description: Implementation of Dijkstra algorithm in C.
Date: 7th April, 2018
Author: Phan Nguyen Vu
*/

#include <stdio.h>
#include <stdlib.h>

#define inf 999 // Assign a large value that describe infinity
#define N 6 // The number of nodes
char node[6] = {'u','v','w','x','y','z'};

int min(a, b){
	if (a>b) {
		return b;
	}
	else{
		return a;
	} 
}

int minDistance(int arr[N], int explored[N]){
	int min_d = 999;
	int idx = 0;
	int count = 0;
	
	for (count=0; count<N; count++){
		if ((min_d > arr[count]) && (arr[count] != 0)){			
			if(explored[count]==1){
				min_d = arr[count];
				idx = count;
			}			
		}
	}
	
	return idx;
}

void printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j]==-1){
    	printf("--> %c ", node[j]);
    	return;
    }
         
    printPath(parent, parent[j]);
 
    printf("--> %c", node[j]);
}
 
// A utility function to print the constructed distance
// array
int printResults(int dist[], int n, int parent[])
{
    int src = 0;
    int i = 0;
    
    printf("Vertex\t  Distance\tPath");
    for (i = 1; i < N; i++)
    {
        printf("\n%c -> %c \t\t %d\t%c ", node[src], node[i], dist[i], node[src]);
        printPath(parent, i);
    }
}

void dijkstra(int c[N][N], int startNode){
	int d[N];	// Create an array to save all shortest paths from the the start node (node 0) --> node i
	int S[N]; 	// Create an array that stores bool value (true or false) to know whether the node have already been explored
	int shortest_path[N];	// Create an array to save shortest path from source
	
	// Initialize loop varibale
	int i = 0;
	int v = startNode;
	int w = startNode;	// The index of the node that among with the shortest path from source
	int dw = 0;
	
	// Initialize value of dist and S
	for(i = 0; i<N; i++){
		shortest_path[i] = -1;
		d[i] = inf;
		S[i] = 1;
	}
	
	// Initialization
	for(v=0; v<N; v++){
		d[v] = c[w][v];
	}
	S[w] = 0;
	w = minDistance(d, S);
	
	for(i=0; i<(N); i++){
		for(v=0; v<N; v++){
			// If the node is not in S (or has not been explored yet) --> update the cost
			if(S[v] == 1){
				dw = d[w];
				d[v] = min(d[v], dw + c[w][v]);
				if (((dw + c[w][v]) == d[v]) && (v != w)) {
					shortest_path[v] = w;
				}
			}					
		}
		// Find the index of the min distance
		S[w] = 0;
		w = minDistance(d, S);
	}
	
	printResults(d, N, shortest_path);
}

int main(){
	// Initialize the graph
	int graph[N][N] = {{0,2,5,1,inf,inf},
	{2,0,3,2,inf,inf},
	{5,3,0,3,1,5},
	{1,2,3,0,1,inf},
	{inf,inf,1,1,0,2},
	{inf,inf,5,inf,2,0}};
	
	dijkstra(graph, 0);
	
	return 0;
}


