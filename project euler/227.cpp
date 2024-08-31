#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const int N = 100, M = 50000;
ld mem[N+1][M+1];
bool vis[N+1][M+1];

const ld pr[] = {1.0l/6.0l, 4.0l/6.0l, 1.0l/6.0l};

ld f(int d, int l){
	if(d == 0 || l == 0) return 0;
	if(vis[d][l]) return mem[d][l];
	ld& ans = mem[d][l];
	ans = 1;
	ld m = 1;
	for(int i : {-1, 0, 1}){
		for(int j : {-1, 0, 1}){
			ld p = pr[i+1], q = pr[j+1];
			int D = d+i+j;
			if(D >= N) D -= N;
			if(D < 0) D += N;
			if(d == D){
				m -= p*q;
			}else{
				ans += f(D, l-1) *p*q;
			}
		}
	}
	vis[d][l] = true;
	ans /= m;
	return ans;
}

int main(){
	cout << fixed << setprecision(10) << f(N/2, M) << "\n";
	return 0;
}