#include <bits/stdc++.h>
using namespace std;

struct disjointSet{
    int N;
    vector<short int> rank;
    vector<int> parent, count;

    disjointSet(int N){
        this->N = N;
        parent.resize(N);
        rank.resize(N);
        count.resize(N);
    }

    void makeSet(int v){
        count[v] = 1;
        parent[v] = v;
    }

    int findSet(int v){
    	if(v == parent[v]) return v;
    	return parent[v] = findSet(parent[v]);
    }

    void unionSet(int a, int b){
        a = findSet(a);
        b = findSet(b);
        if(a == b) return;
        if(rank[a] < rank[b]){
        	parent[a] = b;
            count[b] += count[a];
        }else{
            parent[b] = a;
            count[a] += count[b];
            if(rank[a] == rank[b]){
                ++rank[a];
            }
        }
    }
};

int main(){
	int n, i, x, y, p;
	scanf("%d %d", &n, &i);
	disjointSet DS(n);
	for(int i = 0; i < n; ++i) DS.makeSet(i);
	char op;
	while(i--){
		scanf(" %c", &op);
		if(op == 'A'){
			scanf("%d %d", &x, &y);
			DS.unionSet(x - 1, y - 1);
		}else{
			scanf("%d", &p);
			printf("%d\n", DS.count[DS.findSet(p - 1)]);
		}
	}
	return 0;
}