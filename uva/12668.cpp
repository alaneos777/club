#include <bits/stdc++.h>
using namespace std;

bool kuhn(int u, vector<vector<int>> & graph, vector<bool> & used, vector<int> & left, vector<int> & right){
	if(used[u]) return false;
	used[u] = true;
	for(int v : graph[u]){
		if(right[v] == -1 || kuhn(right[v], graph, used, left, right)){
			right[v] = u;
			left[u] = v;
			return true;
		}
	}
	return false;
}
 
int kuhn(vector<vector<int>> & graph, int l, int r){
	vector<int> left(l, -1), right(r, -1);
	vector<bool> used(l, false);
	bool found;
	do{
		fill(used.begin(), used.end(), false);
		found = false;
		for(int u = 0; u < l; ++u){
			if(left[u] == -1 && !used[u]){
				found |= kuhn(u, graph, used, left, right);
			}
		}
	}while(found);
	int ans = 0;
	for(int u = 0; u < r; ++u){
		if(right[u] != -1){
			++ans;
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	while(cin >> n){
		int r = 0, c = 0;
		vector<vector<char>> grid(n, vector<char>(n));
		vector<vector<int>> rows(n, vector<int>(n, -1));
		vector<vector<int>> cols(n, vector<int>(n, -1));
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				cin >> grid[i][j];
			}
		}
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				if(grid[i][j] == 'X'){
					r++;
				}else{
					rows[i][j] = r;
				}
			}
			r++;
		}
		for(int j = 0; j < n; ++j){
			for(int i = 0; i < n; ++i){
				if(grid[i][j] == 'X'){
					c++;
				}else{
					cols[i][j] = c;
				}
			}
			c++;
		}
		vector<vector<int>> left(r + 1, vector<int>());
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				if(rows[i][j] != -1 && cols[i][j] != -1){
					left[rows[i][j]].push_back(cols[i][j]);
				}
			}
		}
		cout << kuhn(left, r + 1, c + 1) << "\n";
	}
	return 0;
}