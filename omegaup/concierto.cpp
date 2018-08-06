#include <bits/stdc++.h>
using namespace std;

vector<int> changes;
int n, b, m;

vector<vector<int>> mem;

int ans(int pos, int acum){
	if(0 <= acum && acum <= m){
		if(pos == n){
			return acum;
		}else{
			if(mem[pos][acum] == -2) mem[pos][acum] = max(ans(pos + 1, acum - changes[pos]), ans(pos + 1, acum + changes[pos]));
			return mem[pos][acum];
		}
	}else{
		return -1;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	changes.resize(n);
	for(int i = 0; i < n; i++){
		cin >> changes[i];
	}
	cin >> b >> m;
	mem.resize(n, vector<int>(m + 1, -2));
	cout << ans(0, b) << "\n";
	return 0;
}