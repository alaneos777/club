#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const int N = 3;
const ld p = 0.6, q = 1-p;
const ld target = 2;
const ld eps = 1e-9;

map<pair<int, ld>, ld> mem;
map<pair<int, ld>, bool> calc;

ld f(int n, ld d){
	//if(d >= target) return 1;
	if(n == N){
		if(d < target/2 - eps) return 0;
		else if(target/2 <= d + eps && d < target - eps) return p;
		else return 1;
	}else{
		auto key = make_pair(n, d);
		if(calc[key]) return mem[key];
		ld ans = 0;
		for(ld b = 0; b <= d; b += target / pow(2, N-n+1)){
			ld term = p*f(n+1, d+b) + q*f(n+1, d-b);
			ans = max(ans, term);
		}
		ans = max(ans, p*f(n+1, 2*d) + q*f(n+1, 0));
		calc[key] = true;
		return mem[key] = ans;
	}
}

int main(){
	cout << fixed << setprecision(10) << f(1, 1) << "\n";
	return 0;
}

/*
0, p, 1
0, p^2 , p, p(1+q), 1
0, p^3, p^2, p^2(1+q), p^2(1+2q), p(1+pq), p(1+q), p(1+q+q^2), 1
*/