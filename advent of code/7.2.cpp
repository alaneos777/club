#include <bits/stdc++.h>
using namespace std;
 
const regex r1("(.+)\\sbags\\scontain\\s(.+)");
 
int main() {
	string linea;
	map<string, vector<pair<string, int>>> adj;
	set<string> V;
	while(getline(cin, linea)){
		smatch m;
		regex_search(linea, m, r1);
		string from = m[1];
		V.insert(from);
		if(m[2] == "no other bags.") continue;
		stringstream ss(m[2]);
		string word, to;
		int c = 4, cnt = 0;
		while(ss >> word){
			if(c%4 == 0) cnt = stoi(word);
			if(c%4 == 1) to = word;
			if(c%4 == 2) to += " ", to += word;
			if(c%4 == 3){
				adj[from].emplace_back(to, cnt);
				V.insert(to);
			}
			c++;
		}
	}
	function<int(string)> dfs = [&](string u){
		int ans = 0;
		for(const auto & par : adj[u]){
			string v; int cnt;
			tie(v, cnt) = par;
			ans += (1 + dfs(v)) * cnt;
		}
		return ans;
	};
	cout << dfs("shiny gold") << "\n";
	return 0;
}