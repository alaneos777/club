#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> adjList;
typedef vector<vector<bool>> adjMatrix;

struct relation{
	string c1, r, c2;
};

void DFS1(int start, int source, adjList & graph, adjMatrix & tmp){
    tmp[start][source] = true;
    for(int & dest : graph[source]){
        if(!tmp[start][dest]){
            DFS1(start, dest, graph, tmp);
        }
    }
}

adjMatrix transitiveClosure(adjList & graph){
	int V = graph.size();
	adjMatrix tmp(V, vector<bool>(V, false));
	for(int i = 0; i < V; i++){
        DFS1(i, i, graph, tmp);
    }
    return tmp;
}

void DFS2(int start, int source, adjList & graph, adjMatrix & tmp, adjMatrix & hasGraph, vector<int> & visited){
    for(int & dest : graph[source]){
    	tmp[start][dest] = tmp[start][dest] || tmp[start][source] || hasGraph[source][dest];
        if(visited[dest] <= 1){
        	visited[dest]++;
            DFS2(start, dest, graph, tmp, hasGraph, visited);
        }
    }
}

adjMatrix transitiveClosure2(adjList & graph, adjMatrix & hasGraph){
	int V = graph.size();
	adjMatrix tmp(V, vector<bool>(V, false));
	for(int i = 0; i < V; i++){
		vector<int> visited(V);
        DFS2(i, i, graph, tmp, hasGraph, visited);
    }
    return tmp;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	string c1, r, c2;
	set<string> namesOfClasses;
	map<string, int> classes;
	vector<relation> relations(n);
	for(int i = 0; i < n; i++){
		cin >> c1 >> r >> c2;
		namesOfClasses.insert(c1);
		namesOfClasses.insert(c2);
		relations[i] = {c1, r, c2};
	}
	int count = 0;
	for(string clase : namesOfClasses){
		classes[clase] = count++;
	}
	adjList isOnly(count, vector<int>()), isAndHas(count, vector<int>());
	adjMatrix hasGraph(count, vector<bool>(count, false));
	for(int i = 0; i < n; i++){
		int u = classes[relations[i].c1];
		int v = classes[relations[i].c2];
		isAndHas[u].push_back(v);
		if(relations[i].r == "is-a"){
			isOnly[u].push_back(v);
		}else{
			hasGraph[u][v] = true;
		}
	}
	adjMatrix isOnlyMatrix = transitiveClosure(isOnly);
	adjMatrix atLeast1Has = transitiveClosure2(isAndHas, hasGraph);
	for(int i = 0; i < m; i++){
		cin >> c1 >> r >> c2;
		int u = classes[c1];
		int v = classes[c2];
		cout << "Query " << (i + 1) << ": ";
		if(r == "is-a"){
			if(isOnlyMatrix[u][v]){
				cout << "true";
			}else{
				cout << "false";
			}
		}else{
			if(atLeast1Has[u][v]){
				cout << "true";
			}else{
				cout << "false";
			}
		}
		cout << "\n";
	}
	return 0;
}