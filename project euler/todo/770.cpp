#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const int M = 6e4;
int8_t mem[51][51][M];
int opt[51][51][M];
const int m = 1<<14;
const ld T = 1.7;

bool f(int a, int b, int g){
	// a: GIVEs available, b: TAKEs available
	int8_t& ans = mem[a][b][g];
	if(ans != -1) return ans;
	assert(g < M);
	if(a == 0 || b == 0){
		ans = ((1ll*g)<<a) >= T*m;
	}else{
		ans = 0;
		for(int x = 0; x <= g; x++){
			// choose take
			bool v = f(a, b-1, g-x);
			if(!v) continue;
			// choose give
			bool u = f(a-1, b, g+x);
			ans |= (u&v);
			if(ans){
				opt[a][b][g] = x;
				break;
			}
		}
	}
	return ans;
}

int main(){
	memset(mem, -1, sizeof(mem));
	memset(opt, -1, sizeof(opt));
	for(int n = 1; ; ++n){
		bool res = f(n, n, m);
		cout << n << " -> " << res << " " << opt[n][n][m] << "\n";
	}
	return 0;
}