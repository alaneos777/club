#include <bits/stdc++.h>
using namespace std;
 
int main() {
	string ins; int val;
	set<int> vis;
	vector<pair<string, int>> prog;
	while(cin >> ins >> val){
		prog.emplace_back(ins, val);
	}
	int curr = 0, acc = 0;
	while(vis.count(curr)==0){
		vis.insert(curr);
		tie(ins, val) = prog[curr];
		if(ins == "acc") {acc += val; curr++;}
		else if(ins == "jmp"){ curr += val;}
		else curr++;
	}
	cout << acc << "\n";
	return 0;
}