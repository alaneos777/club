#include <bits/stdc++.h>
using namespace std;

void process(string & str, vector<vector<int>> & graph, vector<char> & acum, int & pos){
	char c = str[0];
	int n = str[1] - '0';
	for(int j = 0; j < n; ++j){
		for(int i = 3; i < (int)str.size() - 1; ++i){
			graph[pos].push_back(str[i] - '0');
		}
		acum.push_back(c);
		pos++;
	}
}

bool tryKuhn(int u, vector<bool> & used, vector<int> & left, vector<int> & right, vector<vector<int>> & adjList){
	if(used[u]) return false;
	used[u] = true;
	for(int & v : adjList[u]){
		if(right[v] == -1 || tryKuhn(right[v], used, left, right, adjList)){
			right[v] = u;
			left[u] = v;
			return true;
		}
	}
	return false;
}

vector<pair<int, int>> maxMatching(int l, int r, vector<vector<int>> & graph){
	vector<int> left(l, -1), right(r, -1);
	vector<bool> used(l, false);
	for(int u = 0; u < l; ++u){
		tryKuhn(u, used, left, right, graph);
		fill(used.begin(), used.end(), false);
	}
	vector<pair<int, int>> ans;
	for(int u = 0; u < r; ++u){
		if(right[u] != -1){
			ans.push_back({right[u], u});
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	string str;
	while(getline(cin, str)){
		int pos = 0;
		vector<vector<int>> graph(260);
		vector<char> acum;
		process(str, graph, acum, pos);
		while(true){
			getline(cin, str);
			if(str == "") break;
			process(str, graph, acum, pos);
		}
		auto ans = maxMatching(pos, 10, graph);
		if(ans.size() == pos){
			char cad[11];
			fill(cad, cad + 10, '_');
			cad[10] = '\0';
			for(int i = 0; i < pos; ++i){
				cad[ans[i].second] = acum[ans[i].first];
			}
			cout << cad << "\n";
		}else{
			cout << "!\n";
		}
	}
	return 0;
}