#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

using tup = tuple<int, int, int>;
map<tup, lli> mem[15][15];

inline bool get(int mask, int pos){
	return (mask >> pos) & 1;
}

inline int put(int mask, int pos){
	return mask | (1 << pos);
}

lli f(int m, int n, int i = 0, int j = 0, int a = 0, int b = 0, int c = 0){
	if(mem[i][j].count({a,b,c})) return mem[i][j][{a,b,c}];
	lli ans = 0;
	if(i == m){
		if(j == n-1){
			ans = 1;
		}else{
			ans = f(m, n, 0, j+1, b, c, 0);
		}
	}else{
		// ocupado
		if(get(a, i)){
			ans += f(m, n, i+1, j, a, b, c);
		}else{
			// roja
			if(i+1 < m && j+1 < n && !get(a, i+1) && !get(b, i)){
				ans += f(m, n, i+2, j, put(put(a, i), i+1), put(b, i), c);
			}
			// verde
			if(i+1 < m && j+1 < n && !get(b, i) && !get(b, i+1)){
				ans += f(m, n, i+1, j, put(a, i), put(put(b, i), i+1), c);
			}
			// azul fuerte
			if(i+1 < m && j+1 < n && !get(a, i+1) && !get(b, i+1)){
				ans += f(m, n, i+2, j, put(put(a, i), i+1), put(b, i+1), c);
			}
			// naranja
			if(i-1 >= 0 && j+1 < n && !get(b, i) && !get(b, i-1)){
				ans += f(m, n, i+1, j, put(a, i), put(put(b, i), i-1), c);
			}
			// azul claro
			if(i+2 < m && !get(a, i+1) && !get(a, i+2)){
				ans += f(m, n, i+3, j, put(put(put(a, i), i+1), i+2), b, c);
			}
			// negro
			if(j+2 < n && !get(b, i) && !get(c, i)){
				ans += f(m, n, i+1, j, put(a, i), put(b, i), put(c, i));
			}
		}
	}
	return mem[i][j][{a,b,c}] = ans;
}

int main(){
	cout << f(9, 12) << "\n";
	return 0;
}