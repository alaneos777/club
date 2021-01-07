#include <bits/stdc++.h>
using namespace std;
 
int eval(const vector<pair<string, int>> & prog){
	int n = prog.size();
	string ins; int val;
	vector<bool> vis(n);
	int curr = 0, acc = 0;
	bool loop = false;
	while(curr < n){
		if(vis[curr]){
			loop = true;
			break;
		}
		vis[curr] = true;
		tie(ins, val) = prog[curr];
		if(ins == "acc") {acc += val; curr++;}
		else if(ins == "jmp"){ curr += val;}
		else curr++;
	}
	if(loop) return 1e9;
	else return acc;
}
 
int main() {
	string ins; int val;
	vector<pair<string, int>> prog;
	while(cin >> ins >> val){
		prog.emplace_back(ins, val);
	}
	for(auto& par : prog){
		if(par.first == "jmp"){
			par.first = "nop";
			int x = eval(prog);
			if(x != 1e9) cout << x << endl;
			par.first = "jmp";
		}else if(par.first == "nop"){
			par.first = "jmp";
			int x = eval(prog);
			if(x != 1e9) cout << x << endl;
			par.first = "nop";
		}
	}
	return 0;
}