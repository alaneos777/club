#include <bits/stdc++.h>
using namespace std;

struct node{
	int value;
	node * parent;
	int rank;

	node(int value){
		this->value = value;
		this->parent = this;
		this->rank = 0;
	}
};

struct disjointSet{
	int N;
	vector<node*> nodes;

	disjointSet(int N){
		this->N = N;
		nodes.resize(N);
	}

	void makeSet(int v){
		nodes[v] = new node(v);
	}

	node * findSet(int v){
		node * current = nodes[v];
		if(current -> value != current -> parent -> value){
			current -> parent = findSet(current -> parent -> value);
		}
		return current -> parent;
	}

	node * unionSet(int a, int b){
		node * p1 = findSet(a);
		node * p2 = findSet(b);
		if(p1 -> rank >= p2 -> rank){
			p2 -> parent = p1;
			if(p1 -> rank == p2 -> rank){
				p1 -> rank++;
			}
			return p1;
		}else{
			p1 -> parent = p2;
			return p2;
		}
	}
};

struct edge{
	int source, dest, cost;
	edge(int source, int dest, int cost){
		this -> source = source;
		this -> dest = dest;
		this -> cost = cost;
	}
};

bool comp(const edge * a, const edge * b){
	return a -> cost < b -> cost;
}

int totalWeight(vector<edge*> & graph){
	int sum = 0;
	for(edge * current : graph){
		sum += current -> cost;
	}
	return sum;
}

int main(){
	int n, m;
    cin >> n >> m;
	vector<edge*> graph(m);
	for(int i = 0; i < m; i++){
		int u, v, w;
        cin >> u >> v >> w;
        graph[i] = new edge(u - 1, v - 1, w);
	}
	sort(graph.begin(), graph.end(), comp);

	vector<edge*> spanning;
	disjointSet * dj = new disjointSet(n);
	for(int i = 0; i < n; i++){
		dj -> makeSet(i);
	}
	int i = 0;
	while(spanning.size() < n - 1){
		edge * current = graph[i++];
		if(dj -> findSet(current -> source) != dj -> findSet(current -> dest)){
			spanning.push_back(current);
			dj -> unionSet(current -> source, current -> dest);
		}
	}
	cout << totalWeight(spanning) << "\n";
	return 0;
}