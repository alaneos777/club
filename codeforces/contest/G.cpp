#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> calories, avaliable;
vector<vector<vector<int>>> mem;

int ans(int niv, int ind, bool take){
	if(niv == n){
		return 0;
	}else{
		if(mem[niv][ind][take] == -1){
			mem[niv][ind][take] = max(ans(niv + 1, ind + 1, true) + min(calories[niv], avaliable[ind]), ans(niv + 1, take * max(0, ind - 1), !take));
		}
		return mem[niv][ind][take];
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin >> n >> m;
	calories.resize(n);
	for(int i = 0; i < n; i++){
		cin >> calories[i];
	}
	avaliable.resize(n);
	mem.resize(n, vector<vector<int>>(n, vector<int>(2, -1)));
	avaliable[0] = m;
	for(int i = 1; i < n; i++){
		avaliable[i] = avaliable[i - 1] * 2 / 3;
	}
	cout << ans(0, 0, true) << "\n";
	return 0;
}