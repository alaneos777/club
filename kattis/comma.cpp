#include <bits/stdc++.h>
using namespace std;

struct word{
	string str;
	bool last, comma_prev, comma_after, first;
};

struct action{
	string str;
	char op;
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	string str;
	int n = 0;
	vector<word> words;
	bool first = true, comma_prev = false;
	unordered_map<string, vector<int>> mapeo;
	unordered_map<string, bool> visited_p, visited_a;
	queue<action> actions;
	while(cin >> str){
		bool period = str.back() == '.';
		bool comma = str.back() == ',';
		if(period || comma) str.pop_back();
		words.push_back({str, period, comma_prev, comma, first});
		if(comma)
			actions.push({str, 'a'}); //after
		if(comma_prev)
			actions.push({str, 'p'}); //previous
		mapeo[str].push_back(n++);
		first = period;
		comma_prev = comma;
	}
	while(!actions.empty()){
		action current = actions.front(); actions.pop();
		string & str = current.str;
		vector<int> & positions = mapeo[str];
		if(current.op == 'p'){
			if(visited_p[str]) continue;
			visited_p[str] = true;
			for(int & pos : positions){
				if(words[pos].first) continue;
				if(words[pos].comma_prev) continue;
				words[pos].comma_prev = true;
				if(!words[pos - 1].comma_after){
					actions.push({words[pos - 1].str, 'a'});
					words[pos - 1].comma_after = true;
				}
			}
		}else{
			if(visited_a[str]) continue;
			visited_a[str] = true;
			for(int & pos : positions){
				if(words[pos].last) continue;
				if(words[pos].comma_after) continue;
				words[pos].comma_after = true;
				if(!words[pos + 1].comma_prev){
					actions.push({words[pos + 1].str, 'p'});
					words[pos + 1].comma_prev = true;
				}
			}
		}
	}
	for(int i = 0; i < n; ++i){
		if(i) cout << " ";
		cout << words[i].str;
		if(words[i].comma_after) cout << ",";
		else if(words[i].last) cout << ".";
	}
	return 0;
}