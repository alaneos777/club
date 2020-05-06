#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<bool> is(n+1, true);
	vector<int> primes;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const int M = 6.5e6;
const auto primes = sieve(M);

const lli lim = 1e11;

vector<int> sieve2(int n){
	vector<int> lp(n+1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i&1 ? i : 2);
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j) lp[j] = i;
			}
		}
	}
	return lp;
}

int main(){
	vector<int> primes_1 = {9}, primes_2;
	for(int p : primes){
		if(p % 3 == 1){
			primes_1.push_back(p);
		}else if(p % 3 == 2){
			primes_2.push_back(p);
		}
	}
	sort(primes_1.begin(), primes_1.end());

	vector<array<int, 5>> basics;
	int sz = primes_1.size();
	for(int i = 0; i < sz-4; ++i){
		int a = primes_1[i];
		for(int j = i+1; j < sz-3; ++j){
			int b = primes_1[j];
			if((lli)a*b > lim) break;
			for(int k = j+1; k < sz-2; ++k){
				int c = primes_1[k];
				if((lli)a*b*c > lim) break;
				for(int l = k+1; l < sz-1; ++l){
					int d = primes_1[l];
					if((lli)a*b*c*d > lim) break;
					for(int m = l+1; m < sz; ++m){
						int e = primes_1[m];
						if((lli)a*b*c*d*e > lim) break;
						basics.emplace_back(array<int, 5>{a, b, c, d, e});
					}
				}
			}
		}
	}

	vector<lli> multiples;
	function<void(int, const array<int, 5>, lli)> rec = [&](int pos, const array<int, 5> & f, lli acum){
		if(pos == 5){
			multiples.push_back(acum);
		}else{
			lli p = f[pos];
			if(p == 9) p = 3;
			lli p_pow = 1;
			while(true){
				if(acum * p_pow > lim) break;
				rec(pos + 1, f, acum * p_pow);
				p_pow *= p;
			}
		}
	};

	for(const auto & arr : basics){
		lli acum = 1;
		for(int i = 0; i < 5; ++i) acum *= arr[i];
		rec(0, arr, acum);
	}

	int lim2 = lim / multiples[0];
	const auto lp = sieve2(lim2);
	vector<lli> invalid, acum;
	for(int i = 1; i <= lim2; ++i){
		int n = i;
		bool test = true;
		while(n > 1){
			int p = lp[n];
			while(n % p == 0) n /= p;
			test &= binary_search(primes_2.begin(), primes_2.end(), p);
			if(!test) break;
		}
		if(test) invalid.push_back(i);
	}
	acum.push_back(invalid[0]);
	for(int i = 1; i < invalid.size(); ++i){
		acum.push_back(acum[i-1] + invalid[i]);
	}

	lli sum = 0;

	for(lli n : multiples){
		lli upper = lim / n;
		int pos = upper_bound(invalid.begin(), invalid.end(), upper) - invalid.begin();
		sum += n * acum[pos-1];
		if(n % 3 != 0){
			lli upper = lim / (3*n);
			int pos = upper_bound(invalid.begin(), invalid.end(), upper) - invalid.begin();
			if(pos >= 1) sum += 3*n * acum[pos-1];
		}
	}

	cout << sum << "\n";

	return 0;
}