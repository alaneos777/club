#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const int M = 1e7;

auto lpSieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

const auto lp = lpSieve(M);

auto divs(int n){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n], e = 0;
		while(n % p == 0){
			n /= p;
			e += 2;
		}
		f.emplace_back(p, e);
	}
	vector<lli> divs;
	function<void(int, lli)> dfs = [&](int pos, lli acum){
		if(pos == f.size()){
			divs.push_back(acum);
		}else{
			lli p_pow = 1;
			int p, e;
			tie(p, e) = f[pos];
			for(int i = 0; i <= e; ++i){
				dfs(pos + 1, acum * p_pow);
				p_pow *= p;
			}
		}
	};
	dfs(0, 1);
	sort(divs.begin(), divs.end());
	return divs;
}

lli isSq(lli n){
	lli x = sqrt(n);
	for(lli i = max(0ll, x-1); i <= x+1; ++i){
		if(i*i == n) return i;
	}
	return -1;
}

lli ans = 0;

void process(lli a, lli b){
	lli k = a / 2;
	lli k2 = (lli)k * k;
	for(lli d : divs(k)){
		lli e = k2 / d;
		if(d >= e) break;
		if((d + e) % 2 == 1) continue;
		lli c = (e + d) / 2, h = (e - d) / 2;
		if(a + 2*b + 2*c > M) continue;
		if(0 < 4*c*c - a*a && 4*c*c - a*a < 4*b*b){
			lli m = isSq(k2 + (h + b) * (h + b));
			if(m != -1){
				//cout << a << " " << b << " " << c << " " << h << " " << m << "\n";
				ans += a + 2*b + 2*c;
			}
		}
	}
}

void tree(int a, int b, int l){
	if(a + 2*b >= M) return;
	int A = a, B = b;
	while(A + 2*B < M){
		if(A % 2 == 0 && B % 2 == 1){
			process(A, B);
		}else if(A % 2 == 0 && B % 2 == 0){
			process(A, B);
			process(B, A);
		}else{
			process(B, A);
		}
		A += a, B += b;
	}
	tree(a - 2*b + 2*l, 2*a - b + 2*l, 2*a - 2*b + 3*l);
	tree(-a + 2*b + 2*l, -2*a + b + 2*l, -2*a + 2*b + 3*l);
	tree(a + 2*b + 2*l, 2*a + b + 2*l, 2*a + 2*b + 3*l);
}

int main(){
	tree(3, 4, 5);
	cout << ans << "\n";
	return 0;
}