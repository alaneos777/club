#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9;

auto lpSieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

const lli N = 1e16;
const auto lp = lpSieve(sqrtl(N) + 10);

auto getDivs(int y){
	lli y2 = (lli)y*y;
	vector<pair<int, int>> fact;
	while(y > 1){
		int p = lp[y], a = 0;
		while(y % p == 0){
			y /= p;
			a++;
		}
		fact.emplace_back(p, a*4);
	}
	vector<lli> ans;
	function<void(int, lli)> dfs = [&](int pos, lli acum){
		if(pos == fact.size()){
			if(acum < y2) ans.push_back(acum);
		}else{
			auto[p, a] = fact[pos];
			__int128_t p_pow = 1;
			for(int i = 0; i <= a; ++i){
				__int128_t nxt = acum*p_pow;
				if(nxt >= y2) break;
				dfs(pos+1, nxt);
				p_pow *= p;
			}
		}
	};
	dfs(0, 1);
	sort(ans.begin(), ans.end(), greater<lli>());
	return ans;
}

lli s(lli y){
	lli ans = 0;
	__int128_t y4 = (__int128_t)y*y*y*y;
	/*
	16x^2 + y^4 = z^2 , 1<=x,y,z<=N
	y^4 = z^2 - 16x^2 <= z^2 --> y^2 <= z <= N --> y <= sqrt(N)
	y^4 = de = (z+4x)(z-4x) , d>e , e < y^2 , d > y^2
	z = (d+e)/2
	x = (d-e)/8
	e^2 - 2eN + y^4 <= 0
	e >= N - floor(sqrt(N^2 - y^4))
	d <= 2N
	*/
	for(lli e : getDivs(y)){
		if((__int128_t)e*e - 2*(__int128_t)e*N + y4 > 0) break;
		lli d = y4/e;
		if(((d-e)&7) == 0){
			lli z = (d+e)>>1, x = (d-e)>>3;
			if(__gcd(y, __gcd(x, z)) == 1){
				(ans += x+y+z) %= mod;
				//cout << x << " " << y << " " << z << "\n";
			}
		}
	}
	return ans;
}

atomic<lli> res(0);
atomic<lli> progress(0);
const int cnt = 4;

void f(lli a, lli b){
	lli ans = 0;
	for(lli i = a; i <= b; ++i){
		ans += s(i);
		if(ans >= mod) ans -= mod;
		progress++;
	}
	res += ans;
	if(res >= mod) res -= mod;
}

int main(){
	clock_t start = clock();
	lli limit = sqrtl(N);
	lli work = limit/cnt;
	vector<thread*> threads(cnt);
	for(int i = 0; i < cnt; ++i){
		threads[i] = new thread(f, work * i + 1, i == cnt-1 ? limit : work * (i + 1));
	}
	auto checker = [&limit]{
		while(1){
			cout << "Progress: " << progress << " / " << limit << " (" << (double)progress / limit * 100 << "%)" << endl;
			if(progress == limit) break;
			this_thread::sleep_for(chrono::seconds(3));
		}
	};
	thread watch(checker);
	for(int i = 0; i < cnt; ++i){
		threads[i]->join();
	}
	watch.join();
	clock_t end = clock();
	cout << res << "\n";
	cout << (end-start)/(double)CLOCKS_PER_SEC << "\n";
	return 0;
}