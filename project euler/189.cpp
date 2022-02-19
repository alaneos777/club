#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

map<pair<int, int>, lli> mem[8][15][3];

inline int get(int mask, int pos){
	return (mask >> (2*pos)) & 3;
}

inline int put(int mask, int pos, int val){
	return (mask & ~(3 << (2*pos))) | (val << (2*pos));
}

lli f(int sz, int i, int j, int prev, int msk_up, int msk_curr){
	if(j == 2*i+1){
		if(i == sz-1){
			return 1;
		}else{
			return f(sz, i+1, 0, 0, msk_curr, 0);
		}
	}
	if(mem[i][j][prev].count({msk_up, msk_curr})) return mem[i][j][prev][{msk_up, msk_curr}];
	lli ans = 0;
	if(j%2 == 0){
		for(int c = 0; c < 3; ++c){
			if(j == 0 || c != prev){
				ans += f(sz, i, j+1, c, msk_up, put(msk_curr, j/2, c));
			}
		}
	}else{
		for(int c = 0; c < 3; ++c){
			if(c != prev && c != get(msk_up, (j-1)/2)){
				ans += f(sz, i, j+1, c, msk_up, msk_curr);
			}
		}
	}
	return mem[i][j][prev][{msk_up, msk_curr}] = ans;
}

int main(){
	cout << f(8, 0, 0, 0, 0, 0) << "\n";
	return 0;
}