#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ull = unsigned long long int;

const lli mod = 1e9 + 7;

vector<int> primes;
vector<vector<pair<int, int>>> sieve(int n){
	vector<vector<pair<int, int>>> f(n+1);
	vector<int> cnt(n+1), acum(n+1);
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){ //case base: f(p)
			f[i].emplace_back(primes.size(), 1);
			primes.push_back(i);
			cnt[i] = 1;
			acum[i] = i;
		}
		for(int j = 0; j < primes.size(); ++j){
			int p = primes[j];
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){ //gcd(i, p) != 1
				f[d] = f[i / acum[i]];
				f[d].emplace_back(j, cnt[i] + 1);
				cnt[d] = cnt[i] + 1;
				acum[d] = acum[i] * p;
				break;
			}else{ //gcd(i, p) = 1
				f[d] = f[i];
				f[d].emplace_back(j, 1);
				cnt[d] = 1;
				acum[d] = p;
			}
		}
	}
	return f;
}

vector<lli> allInverses(lli n){
	vector<lli> ans(n+1);
	ans[1] = 1;
	for(lli i = 2; i <= n; ++i)
		ans[i] = mod - (mod / i) * ans[mod % i] % mod;
	return ans;
}

vector<vector<pair<int, int>>> facts = sieve(300);
vector<lli> invs = allInverses(300);

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

struct SegmentTreeDin{
	SegmentTreeDin *left, *right;
	int l, r;
	lli prod, lazy1;
	ull conj, lazy2;
	bool pending;
 
	SegmentTreeDin(int start, int end, vector<lli> & arr): left(NULL), right(NULL), l(start), r(end), prod(1), conj(0), lazy1(1), lazy2(0), pending(false){
		if(l == r){
			prod = arr[l];
			for(auto & par : facts[arr[l]])
				conj |= 1ll<<par.first;
		}else{
			int half = l + ((r - l) >> 1);
			left = new SegmentTreeDin(l, half, arr);
			right = new SegmentTreeDin(half+1, r, arr);
			prod = left->prod * right->prod % mod;
			conj = left->conj | right->conj;
		}
	}
 
	void propagate(lli dif1, ull dif2){
		prod = prod * powerMod(dif1, r-l+1) % mod;
		conj |= dif2;
		if(l != r){
			left->lazy1 = left->lazy1 * dif1 % mod;
			right->lazy1 = right->lazy1 * dif1 % mod;
			left->lazy2 |= dif2;
			right->lazy2 |= dif2;
			left->pending = right->pending = true;
		}
	}
 
	lli prod_numbers(int start, int end){
		if(pending){
			propagate(lazy1, lazy2);
			pending = false;
			lazy1 = 1, lazy2 = 0;
		}
		if(end < l || r < start) return 1;
		if(start <= l && r <= end) return prod;
		else return left->prod_numbers(start, end) * right->prod_numbers(start, end) % mod;
	}

	ull union_conj(int start, int end){
		if(pending){
			propagate(lazy1, lazy2);
			pending = false;
			lazy1 = 1, lazy2 = 0;
		}
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return conj;
		else return left->union_conj(start, end) | right->union_conj(start, end);
	}

	lli prod_primes(int start, int end){
		ull pr = union_conj(start, end);
		lli ans = 1;
		for(int i = 0; i < 64; ++i){
			if(pr & (1ll << i)){
				lli p = primes[i];
				ans = ans * (p - 1) % mod * invs[p] % mod;
			}
		}
		return ans;
	}
 
	void update(int start, int end, lli dif){
		if(pending){
			propagate(lazy1, lazy2);
			pending = false;
			lazy1 = 1, lazy2 = 0;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end){
			ull mask = 0;
			for(auto & par : facts[dif])
				mask |= 1ll<<par.first;
			propagate(dif, mask);
		}else{
			left->update(start, end, dif);
			right->update(start, end, dif);
			prod = left->prod * right->prod % mod;
			conj = left->conj | right->conj;
		}
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q, l, r, x;
	string action;
	cin >> n >> q;
	vector<lli> a(n);
	for(lli & ai : a) cin >> ai;
	SegmentTreeDin st(0, n-1, a);
	while(q--){
		cin >> action >> l >> r;
		if(action == "MULTIPLY"){
			cin >> x;
			st.update(l-1, r-1, x);
		}else{
			cout << (st.prod_numbers(l-1, r-1) * st.prod_primes(l-1, r-1)) % mod << "\n";
		}
	}
	return 0;
}