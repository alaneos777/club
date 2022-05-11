#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 1000;
bitset<M+1> mem[M+1][M+1];
bitset<M+1> calc[M+1][M+1];

bool f(int a, int b, int c){
	if(a == 0 && b == 0 && c == 0) return false;
	if(b < a) swap(b, a);
	if(c < b){
		swap(c, b);
		if(b < a){
			swap(a, b);
		}
	}
	if(calc[a][b][c]) return mem[a][b][c];
	calc[a][b][c] = true;
	bool win = false;
	for(int i = c; i >= 1; --i){
		if(win) break;
		if(a-i >= 0) win = win || !f(a-i, b, c);
		if(b-i >= 0) win = win || !f(a, b-i, c);
		if(c-i >= 0) win = win || !f(a, b, c-i);
		if(a-i >= 0 && b-i >= 0) win = win || !f(a-i, b-i, c);
		if(a-i >= 0 && c-i >= 0) win = win || !f(a-i, b, c-i);
		if(b-i >= 0 && c-i >= 0) win = win || !f(a, b-i, c-i);
		if(a-i >= 0 && b-i >= 0 && c-i >= 0) win = win || !f(a-i, b-i, c-i);
	}
	if(!win){
		for(int i = 1; a+i <= b; ++i){
			calc[a+i][b][c] = mem[a+i][b][c] = true;
		}
		for(int i = 1; b+i <= c; ++i){
			calc[a][b+i][c] = mem[a][b+i][c] = true;
			calc[a+i][b+i][c] = mem[a+i][b+i][c] = true;
		}
		for(int i = 1; c+i <= M; ++i){
			calc[a][b][c+i] = mem[a][b][c+i] = true;
		}
		for(int i = 1; a+i <= b && c+i <= M; ++i){
			calc[a+i][b][c+i] = mem[a+i][b][c+i] = true;
		}
		for(int i = 1; c+i <= M; ++i){
			calc[a][b+i][c+i] = mem[a][b+i][c+i] = true;
		}
		for(int i = 1; c+i <= M; ++i){
			calc[a+i][b+i][c+i] = mem[a+i][b+i][c+i] = true;
		}
	}
	return mem[a][b][c] = win;
}

int main(){
	clock_t start = clock();
	lli ans = 0;
	for(int x = 0; x <= M; ++x){
		for(int y = x; y <= M; ++y){
			for(int z = y; z <= M; ++z){
				if(!f(x, y, z)){
					ans += x+y+z;
				}
			}
		}
	}
	cout << fixed << setprecision(3) << double(clock() - start)/CLOCKS_PER_SEC << "\n";
	cout << ans << "\n";
	return 0;
}