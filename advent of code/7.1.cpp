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
	map<string, bool> is;
	function<bool(string)> dfs = [&](string u){
		bool ans = false;
		for(auto par : adj[u]){
			string v; int cnt;
			tie(v, cnt) = par;
			ans |= (v == "shiny gold" | dfs(v));
		}
		return is[u] = ans;
	};
	int ans = 0;
	for(string u : V){
		if(!is.count(u)) dfs(u);
		ans += is[u];
	}
	cout << ans << "\n";
	return 0;
}