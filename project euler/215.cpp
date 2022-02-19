#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

map<pair<int, int>, lli> mem[40][40];

inline int get(int mask, int pos){
	return (mask >> (2*pos)) & 3;
}

inline int put(int mask, int pos, int val){
	return (mask & ~(3 << (2*pos))) | (val << (2*pos));
}

lli W(int m, int n, int i = 0, int j = 0, int prev = 0, int curr = 0){
	if(mem[i][j].count({prev, curr})) return mem[i][j][{prev, curr}];
	lli ans = 0;
	if(i == m){
		ans = W(m, n, 0, j+1, curr, 0);
	}else if(j == n){
		ans = (prev==0);
	}else{
		bool valid = true;
		if(i == 0){
			for(int k = 0; k+1 < m; ++k){
				if(get(prev, k) == 0 && get(prev, k+1) == 0){
					valid = false;
					break;
				}
			}
		}
		if(valid || j == 0){
			if(get(prev, i) == 0){
				ans += W(m, n, i+1, j, prev, put(curr, i, 2));
				ans += W(m, n, i+1, j, prev, put(curr, i, 1));
			}else{
				ans += W(m, n, i+1, j, prev, put(curr, i, get(prev, i) - 1));
			}
		}
	}
	return mem[i][j][{prev, curr}] = ans;
}

int main(){
	cout << W(10, 32) << "\n";
	return 0;
}