#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning (disable:4996)
#define INF 2140000
#define OUTOFQ -1

typedef struct {
	int index;
	double weight;
}graph;

typedef struct {
	int index;
	int x;
	int y;
}Vertex;

graph* key = NULL;//save the weight with node's number
graph* Q = NULL;//priority queue-->it's eventually gonna be deleted if the algorithm finish
Vertex* V = NULL;//Vertex information(index, x, y)
Vertex* adj = NULL;//save the adjustant nodes
int num;
int count;//Q에 들어있는 버텍스의 갯수. Q에서 하나씩 빠질수록 하나씩 줄어든다.

/*using in the priority queue choosing*/
int compare(const void* A, const void* B)
{
	graph* ptrA = (graph*)A;
	graph* ptrB = (graph*)B;

	if (ptrA->weight < ptrB->weight) return -1;
	else if (ptrA->weight == ptrB->weight) return 0;
	else return 1;

}
/*priority queue choose the minimum weight*/
int extract_min() {
	int u;
	qsort(Q, count, sizeof(graph), compare);//sort to find minimum weight
	u = Q[0].index;//minimum weight one

	/*delete the chosen vertex*/
	Q[0].index = Q[count - 1].index;
	Q[0].weight = Q[count - 1].weight;
	Q[count - 1].index = OUTOFQ;
	Q[count - 1].weight = OUTOFQ;

	count--;
	return u;
}

/*check it's selected as a part of minimum spanning tree or not */
/*to avoid cycle*/
int iscontainedinQ(int index) {
	for (int i = 0; i < count; i++) {
		if (Q[i].index == index)return 1;
		
	}
	return 0;
}

/*find the length between two nodes*/
double W(int u, int v) {
	int ux=0, uy=0, vx=0, vy=0;
	for (int i = 0; i < num; i++) {
		if (V[i].index == u) {
			ux = V[i].x;
			uy = V[i].y;
		}
		if (V[i].index == v) {
			vx = V[i].x;
			vy = V[i].y;
		}
	}
	int a = ux - vx;
	int b = uy - vy;

	double c = sqrt((a * a) + (b * b));
	return c;
}

/*assign V to Q*/
void assignall() {
	for (int i = 0; i < num; i++) {
		Q[i].index = key[i].index;
		Q[i].weight = key[i].weight;
	}
}

/*prims algorithm*/
void prims() {
	
	assignall();//Q <- V
	count = num;

	for (int i = 0; i < num; i++) {//key[v] ← ∞ for all v ∈ V
		key[i].weight = INF;
		Q[i].weight = INF;
	}
	/*key[s] ← 0 for some arbitrary s ∈ V*/
	key[0].weight = 0;
	Q[0].weight = 0;
	
	while (count!=0) {//while Q ≠ zero set
		int u = extract_min(); //do u ← EXTRACT-MIN ( Q)

		/*make a adjustant nodes set*/
		for (int i=0; i < count; i++) {
			int k = Q[i].index;//Q에 남아있는 애들의 index
			adj[i].index = k;
			adj[i].x = V[k].x;//남아있는 노드의 index에 대한 x,y정보를 V에서 가져와
			adj[i].y = V[k].y;
		}

		/*in this example, all nodes are adjustant nodes. so assign all of them.
		for  each v ∈ Adj[u]*/
		for (int i = 0; i < count; i++) {
			int v = adj[i].index;
			if (iscontainedinQ(v) ) {//do if v ∈ Q and w(u, v) < key[v] 
				double weighttmp = W(u, v);
				if (weighttmp < key[v].weight) {
					key[v].weight = weighttmp;//then key[v] ← w(u, v) 
					for (int i = 0; i < count; i++) {//also change the Q value
						if (key[v].index == Q[i].index) Q[i].weight = weighttmp;
					}
				}
			}
		}
		
	}
	float sum=0;
	for (int i = 0; i < num; i++) {
		sum += key[i].weight;
	}
	printf("%f", sum);
}

void main() {
	
	scanf("%d", &num);

	key = (graph*)malloc(sizeof(graph) * num);
	Q = (graph*)malloc(sizeof(graph) * num);
	V = (Vertex*)malloc(sizeof(Vertex) * num);
	adj = (Vertex*)malloc(sizeof(adj) * num);

	for (int i = 0; i < num; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		V[i].index = i;
		V[i].x = x;
		V[i].y = y;
		key[i].index = i;
	}
	prims();
}




