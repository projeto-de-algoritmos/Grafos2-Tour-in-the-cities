#include <bits/stdc++.h> 
using namespace std; 

class Edge 
{ 
	public: 
	int src, dest, weight; 
}; 

class Graph 
{ 
	public: 
	int V, E; 

	Edge* edge; 
}; 

Graph* createGraph(int V, int E) 
{ 
	Graph* graph = new Graph; 
	graph->V = V; 
	graph->E = E; 

	graph->edge = new Edge[E]; 

	return graph; 
} 
 
class subset 
{ 
	public: 
	int parent; 
	int rank; 
}; 
 
int find(subset subsets[], int i) {  
	if (subsets[i].parent != i) 
		subsets[i].parent = find(subsets, subsets[i].parent); 

	return subsets[i].parent; 
} 


void Union(subset subsets[], int x, int y) 
{ 
	int xroot = find(subsets, x); 
	int yroot = find(subsets, y); 

	
	if (subsets[xroot].rank < subsets[yroot].rank) 
		subsets[xroot].parent = yroot; 
	else if (subsets[xroot].rank > subsets[yroot].rank) 
		subsets[yroot].parent = xroot; 
	
	else
	{ 
		subsets[yroot].parent = xroot; 
		subsets[xroot].rank++; 
	} 
} 
 
int myComp(const void* a, const void* b) { 
	Edge* a1 = (Edge*)a; 
	Edge* b1 = (Edge*)b; 
	return a1->weight > b1->weight; 
} 

void KruskalMST(Graph* graph, char answer_points[]) 
{ 
	int V = graph->V; 
	Edge result[V];
	int e = 0;
	int i = 0;
	int minimumCost = 0;

	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp); 

	subset *subsets = new subset[( V * sizeof(subset) )]; 
 
	for (int v = 0; v < V; ++v) 
	{ 
		subsets[v].parent = v; 
		subsets[v].rank = 0; 
	} 

	while (e < V - 1 && i < graph->E) { 
		Edge next_edge = graph->edge[i++]; 

		int x = find(subsets, next_edge.src); 
		int y = find(subsets, next_edge.dest); 

		if (x != y) { 
			minimumCost += next_edge.weight;
			result[e++] = next_edge; 
			Union(subsets, x, y); 
		}
	} 
	
	cout<<"Shortest way" << endl; 
	for (i = 0; i < e; ++i) 
		cout<<result[i].src<<" -- "<<result[i].dest << endl;
		// Show the cost of MST
		//cout<<result[i].src<<" -- "<<result[i].dest << " = " << result[i].weight << endl;

	if(answer_points[0] == 'S' || answer_points[0] == 's'){
		cout<<"Points" << endl; 
		cout << minimumCost << endl;
	}
	return; 
} 

int main() { 
	int vertices=0, edges = 0;
	char answer[3];
	char answer_points[3];
	cout << "How many sights do you want to visit ?" << endl; 
	cin >> vertices;
	cout << "How many connections do you want to make by then ?" << endl;
	cin >> edges;

	Graph* graph = createGraph(vertices, edges); 

    for(int aux =0; aux < edges; aux++){
        cin >> graph->edge[aux].src; 
	    cin >> graph->edge[aux].dest; 
	    cin >> graph->edge[aux].weight; 
    }

	cout << "Want to know how many points you spend to follow the shorter paths ?" << endl;
	cin >> answer_points;

	KruskalMST(graph, answer_points); 

	return 0; 
} 
