#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const ld eps = 1e-16;
ld LogFact[1111];

ld get(int N, ld f, ld target){
	ld a = 1 + 2*f, b = 1 - f;
	ld p = 0;
	for(int k = 0; k <= N; ++k){
		if(k*logl(a) + (N-k)*logl(b) >= logl(target)){
			p += expl(LogFact[N] - LogFact[k] - LogFact[N-k] - N*logl(2));
		}
	}
	return p;
}

int main(){
	int N = 1000;
	ld target = 1e9;
	for(int i = 1; i <= N; ++i){
		LogFact[i] = LogFact[i-1] + logl(i);
	}
	ld l = 0, r = 1;
	while(abs(l-r) >= eps){
		ld a = l + (r-l)/3;
		ld b = r - (r-l)/3;
		if(get(N, a, target) < get(N, b, target)){
			l = a;
		}else{
			r = b;
		}
	}
	ld f = (l+r)/2;
	cout << fixed << setprecision(12) << f << " " << get(N, f, target) << "\n";
	return 0;
}