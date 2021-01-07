#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const regex reg("(.+) \\(contains (.+)\\)");

auto split(const string & t){
	string s;
	for(char c : t){
		if(c != ',') s += c;
	}
	stringstream ss(s);
	vector<string> ans;
	string str;
	while(ss >> str){
		ans.push_back(str);
	}
	return ans;
}

int main(){
	map<string, int> map_ing, map_all, freq_ing;
	int sz_ing = 0, sz_all = 0;
	vector<string> lst_ing, lst_all;
	auto id_ing = [&](const string & s){
		if(map_ing.count(s)) return map_ing[s];
		lst_ing.push_back(s);
		return map_ing[s] = sz_ing++;
	};
	auto id_all = [&](const string & s){
		if(map_all.count(s)) return map_all[s];
		lst_all.push_back(s);
		return map_all[s] = sz_all++;
	};

	vector<vector<int>> adj(100);

	string line;
	while(getline(cin, line)){
		smatch m;
		regex_match(line, m, reg);
		vector<string> ingredients = split(m[1]);
		vector<string> allergens = split(m[2]);
		for(const string & t : ingredients){
			freq_ing[t]++;
		}
		for(const string & s : allergens){
			vector<int> tmp;
			for(const string & t : ingredients){
				tmp.push_back(id_ing(t));
			}
			sort(tmp.begin(), tmp.end());
			if(adj[id_all(s)].empty()){
				adj[id_all(s)] = tmp;
			}else{
				vector<int> out;
				set_intersection(adj[id_all(s)].begin(), adj[id_all(s)].end(), tmp.begin(), tmp.end(), back_inserter(out));
				adj[id_all(s)] = out;
			}
		}
	}

	auto maxMatching = [&](int l, int r){
		vector<int> left(l, -1), right(r, -1);
		vector<bool> used(l);

		function<bool(int)> tryKuhn = [&](int u){
			if(used[u]) return false;
			used[u] = true;
			for(int v : adj[u]){
				if(right[v] == -1 || tryKuhn(right[v])){
					right[v] = u;
					left[u] = v;
					return true;
				}
			}
			return false;
		};

		for(int u = 0; u < l; ++u){
			tryKuhn(u);
			fill(used.begin(), used.end(), false);
		}
		vector<pair<int, int>> ans;
		for(int u = 0; u < r; ++u){
			if(right[u] != -1){
				ans.emplace_back(right[u], u);
			}
		}
		return ans;
	};

	auto match = maxMatching(sz_all, sz_ing);
	vector<bool> used(sz_ing);
	for(const auto & par : match){
		used[par.second] = true;
	}

	int ans = 0;
	for(int i = 0; i < sz_ing; ++i){
		if(!used[i]){
			ans += freq_ing[lst_ing[i]];
		}
	}
	cout << ans << endl;

	return 0;
}