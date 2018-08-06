#include <bits/stdc++.h>
using namespace std;

string bfs(vector<set<int>> & graph, int start, set<int> & digits){
	queue<int> pending;
	pending.push(start);
	vector<int> previous(graph.size(), -1);
	int level = 1;
	int last = -1;
	while(!pending.empty()){
		int length = pending.size();
		while(length--){
			int current = pending.front();
			pending.pop();
			if(level == digits.size()){
				last = current;
				break;
			}
			for(int dest : graph[current]){
				pending.push(dest);
				previous[dest] = current;
			}
		}
		level++;
	}
	stack<int> result;
	while(last != -1){
		result.push(last);
		last = previous[last];
	}
	stringstream ss;
	while(!result.empty()){
		ss << result.top();
		result.pop();
	}
	return ss.str();
}

int main(){
	ifstream in("p079_keylog.txt");
	vector<set<int>> graph(10);
	set<int> digits;
	string line;
	while(in >> line){
		for(int i = 0; i < line.size(); i++){
			digits.insert(line[i] - '0');
			for(int j = i + 1; j < line.size(); j++){
				graph[line[i] - '0'].insert(line[j] - '0');
			}
		}
	}
	for(int i : digits){
		cout << bfs(graph, i, digits) << "\n";
	}
	return 0;
}