#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

const int N = 1e7;
vector<ld> log10_fact(N+1);

const ld ln10 = logl(10);
const ld eps = 1e-9;

ld eval(ld c){
	ld f = c * ln10;
	int M = min(N-1, (int)round(f - 0.5l));
	ld ans = M * log10l(f) - log10_fact[M] - c;
	ld sum = 0;
	ld b = 1;
	for(int k = M; k >= 0; --k){
		if(k != M) sum += b;
		b *= k / f;
		if(b < eps) break;
		if(k != M) assert(b < 1);
	}
	b = 1;
	for(int k = M; k < N; ++k){
		if(k != M) sum += b;
		b *= f / (k+1);
		if(b < eps) break;
		if(k != M) assert(b < 1);
	}
	ans += log1pl(sum) / ln10;
	return ans;
}

int main(){
	for(int i = 2; i <= N; ++i){
		log10_fact[i] = log10_fact[i-1] + log10l(i);
	}
	ld obj = log10l(0.25l);
	ld l = 0.4*N, r = 0.5*N, c;
	while(abs(l-r) >= 1e-5){
		c = (l + r) / 2;
		if(eval(c) > obj){
			l = c;
		}else{
			r = c;
		}
	}
	cout << fixed << setprecision(2) << c << " " << powl(10, eval(c)) << "\n";
	return 0;
}