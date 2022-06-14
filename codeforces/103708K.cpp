#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 6e4;
bitset<M+1> mem[50];
bitset<M+1> clc[50];
bitset<M+1> pre;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int k, p;
	cin >> k >> p;
	vector<int> c(p);
	for(int& ci : c){
		cin >> ci;
	}
	function<bool(int, int)> f = [&](int n, int pos) -> bool {
		if(pos < 0 || n < 0) return 0;
		if(n == 0) return 1;
		if(clc[pos][n]) return mem[pos][n];
		clc[pos][n] = true;
		return mem[pos][n] = f(n-c[pos], pos) || f(n, pos-1);
	};
	for(int n = 0; n <= M; ++n){
		pre[n] = f(n, p-1);
	}
	while(k--){
		int ni;
		cin >> ni;
		int nf = ni;
		while(!pre[nf]) ++nf;
		cout << nf-ni << "\n";
	}
	return 0;
}