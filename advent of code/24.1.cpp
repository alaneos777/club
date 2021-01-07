#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using pii = pair<int, int>;

pii move(int x, int y, const string & dir){
	if(dir == "e"){
		return {x+1, y};
	}else if(dir == "w"){
		return {x-1, y};
	}else if(dir == "nw"){
		if(abs(y) % 2 == 1){
			return {x, y-1};
		}else{
			return {x-1, y-1};
		}
	}else if(dir == "ne"){
		if(abs(y) % 2 == 1){
			return {x+1, y-1};
		}else{
			return {x, y-1};
		}
	}else if(dir == "sw"){
		if(abs(y) % 2 == 1){
			return {x, y+1};
		}else{
			return {x-1, y+1};
		}
	}else if(dir == "se"){
		if(abs(y) % 2 == 1){
			return {x+1, y+1};
		}else{
			return {x, y+1};
		}
	}else{
		assert(0);
		return {0, 0};
	}
}

int main(){
	string line;
	map<pii, bool> grid;
	while(cin >> line){
		vector<string> ins;
		int i = 0, n = line.size();
		while(i < n){
			if(line[i] == 'e'){
				ins.push_back("e");
				i++;
			}else if(line[i] == 'w'){
				ins.push_back("w");
				i++;
			}else if(line[i] == 'n'){
				i++;
				if(line[i] == 'w'){
					ins.push_back("nw");
					i++;
				}else if(line[i] == 'e'){
					ins.push_back("ne");
					i++;
				}
			}else if(line[i] == 's'){
				i++;
				if(line[i] == 'w'){
					ins.push_back("sw");
					i++;
				}else if(line[i] == 'e'){
					ins.push_back("se");
					i++;
				}
			}
		}
		int x = 0, y = 0;
		for(const string & s : ins){
			tie(x, y) = move(x, y, s);
		}
		grid[{x, y}] ^= 1;
	}
	int ans = 0;
	for(const auto & par : grid){
		ans += par.second;
	}
	cout << ans << endl;
	return 0;
}