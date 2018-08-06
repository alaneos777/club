#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int l, r, u;
	int caso = 1;
	while(cin >> l >> u >> r){
		if(l == 0 && r == 0 && u == 0) break;
		vector<int> buttons(r);
		for(int i = 0; i < r; ++i){
			cin >> buttons[i];
		}
		queue<int> Q;
		Q.push(l);
		bool found = false;
		vector<bool> visited(1e4, false);
		vector<int> dist(1e4);
		dist[l] = 0;
		while(!Q.empty()){
			int current = Q.front(); Q.pop();
			visited[current] = true;
			if(current == u){
				found = true;
				break;
			}
			for(int & button : buttons){
				int dest = current + button;
				if(dest >= 1e4) dest -= 1e4;
				if(!visited[dest]){
					dist[dest] = dist[current] + 1;
					visited[dest] = true;
					Q.push(dest);
				}
			}
		}
		cout << "Case " << caso++ << ": ";
		if(found){
			cout << dist[u] << "\n";
		}else{
			cout << "Permanently Locked\n";
		}
	}
	return 0;
}