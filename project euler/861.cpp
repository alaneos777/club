#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct SumPrimePi{
	int v;
	lli n;
	vector<lli> lo, hi;
	vector<int> primes;

	SumPrimePi(lli n): n(n), v(sqrt(n)){
		lo.resize(v+2), hi.resize(v+2);
	}

	void build(){
		lli p, q, j, end, i, d;
		lli temp;
		for(p = 1; p <= v; p++){
			lo[p] = p - 1;
			hi[p] = n/p - 1;
		}
		for(p = 2; p <= v; p++){
			if(lo[p] == lo[p-1]) continue;
			primes.push_back(p);
			temp = lo[p-1];
			q = p * p;
			end = (v <= n/q) ? v : n/q;
			for(i = 1; i <= end; ++i){
				d = i * p;
				if(d <= v)
					hi[i] -= (hi[d] - temp);
				else
					hi[i] -= (lo[n/d] - temp);
			}
			for(i = v; i >= q; i--){
				lo[i] -= (lo[i/p] - temp);
			}
		}
	}

	lli get(lli i) const{
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

auto divsSieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j].push_back(i);
		}
	}
	return divs;
}

const auto divs = divsSieve(200);

vector<vector<int>> generateFactorizations(int m, int n){
	if(m == 1 && n == 1) return {{}};
	if(m == 1) return {};
	if(n == 1) return {{}};
	vector<vector<int>> ans;
	for(int d : divs[n]){
		if(d > m) break;
		if(d%2 == 1) continue;
		auto facts = generateFactorizations(d, n/d);
		for(auto& fact : facts){
			fact.push_back(d);
		}
		ans.insert(ans.end(), facts.begin(), facts.end());
	}
	return ans;
}

SumPrimePi pi(1);

lli Q(lli n, int k){
	auto facts = generateFactorizations(2*k, 2*k);
	set<vector<int>> newFacts;
	for(const auto& fact : facts){
		for(int msk = 0; msk < (1<<fact.size()); ++msk){
			vector<int> newFact;
			for(int i = 0; i < fact.size(); ++i){
				if(msk & (1<<i)){
					newFact.push_back(fact[i]);
				}else{
					newFact.push_back(fact[i]-1);
				}
			}
			sort(newFact.begin(), newFact.end(), greater<int>());
			newFacts.insert(newFact);
		}
	}
	function<lli(const vector<int>&, int, int, lli, const set<int>&)> go = [&](const vector<int>& fact, int pos, int start, lli n, const set<int>& forbidden) -> lli{
		if(pos == fact.size()-1){
			lli lo = 1 + (start == 0 ? 0 : pi.primes[start-1]), hi = powl(n, 1.0l/fact[pos]);
			if(lo > hi) return 0;
			lli ans = pi.get(hi) - pi.get(lo - 1);
			for(int p : forbidden){
				if(lo <= p && p <= hi) ans--;
			}
			return ans;
		}
		lli ans = 0;
		for(int i = start; i < pi.primes.size(); ++i){
			int p = pi.primes[i];
			if(forbidden.count(p)) continue;
			lli nxt_n = n;
			for(int j = 0; j < fact[pos]; ++j){
				nxt_n /= p;
				if(nxt_n == 0) break;
			}
			if(nxt_n == 0) break;
			auto newForbidden = forbidden;
			newForbidden.insert(p);
			lli curr = go(fact, pos+1, fact[pos] == fact[pos+1] ? i+1 : 0, nxt_n, newForbidden);
			if(curr == 0) break;
			ans += curr;
		}
		return ans;
	};
	lli ans = 0;
	for(const auto& fact : newFacts){
		ans += go(fact, 0, 0, n, {});
	}
	return ans;
}

int main(){
	lli N = 1e12;
	pi = SumPrimePi(N);
	pi.build();
	lli ans = 0;
	for(int k = 2; k <= 10; ++k){
		ans += Q(N, k);
	}
	cout << ans << "\n";
	return 0;
}