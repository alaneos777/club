#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int mod = 1e9+123;

map<tuple<int, uint16_t, uint16_t, int>, int> mem;

inline uint16_t getBit(uint16_t m, int i){
	return (m >> i) & 1;
}

inline void flipBit(uint16_t & m, int i){
	m ^= (1 << i);
}

inline void setBit(uint16_t & m, int i){
	m |= (1 << i);
}

int q(int idx, uint16_t p, uint16_t a, bool f, int zero_prefix, int zero_count){
	if(idx == 0){
		bool t = true;
		for(int d = 0; d <= 9; ++d){
			if(d != 0 && getBit(a, d)){
			    t &= (d % 2 == getBit(p, d));
			}else if(d == 0 && zero_count > zero_prefix){
				t &= ((zero_count - zero_prefix) % 2 == 0);
			}
		}
		return t;
	}
	auto key = make_tuple(idx, p, a, zero_prefix - zero_count);
	if(mem.count(key)) return mem[key];
	int ans = 0;
	for(int d = 0; d <= 9; ++d){
		uint16_t c = p;
		uint16_t A = a;
		flipBit(c, d);
		setBit(A, d);
		ans += q(idx-1, c, A, f && (d==0), f && d==0 ? zero_prefix+1 : zero_prefix, zero_count + (d == 0));
		if(ans >= mod) ans -= mod;
	}
	return mem[key] = ans;
}

lli inverse(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(r0 == 1);
	if(s0 < 0) s0 += n;
	return s0;
}

vector<lli> BerlekampMassey(const vector<lli> & init){
	vector<lli> cur, ls;
	lli ld;
	for(int i = 0, m; i < init.size(); ++i){
		lli eval = 0;
		for(int j = 0; j < cur.size(); ++j)
			eval = (eval + init[i-j-1] * cur[j]) % mod;
		eval -= init[i];
		if(eval < 0) eval += mod;
		if(eval == 0) continue;
		if(cur.empty()){
			cur.resize(i + 1);
			m = i;
			ld = eval;
		}else{
			lli k = eval * inverse(ld, mod) % mod;
			vector<lli> c(i - m - 1);
			c.push_back(k);
			for(int j = 0; j < ls.size(); ++j)
				c.push_back((mod-ls[j]) * k % mod);
			if(c.size() < cur.size()) c.resize(cur.size());
			for(int j = 0; j < cur.size(); ++j){
				c[j] += cur[j];
				if(c[j] >= mod) c[j] -= mod;
			}
			if(i - m + ls.size() >= cur.size())
				ls = cur, m = i, ld = eval;
			cur = c;
		}
	}
	if(cur.empty()) cur.push_back(0);
	reverse(cur.begin(), cur.end());
	return cur;
}

lli rec(const vector<lli> & P, const vector<lli> & init, lli n){
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				(R[i + j + d] += ans[i] * ans[j]) %= mod;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += ans[i] * init[i]) %= mod;
	return nValue;
}

int main(){
	/*
	vector<lli> init;
	for(int n = 1; n <= 42; ++n){
		init.push_back(q(n, 0, 0, true, 0, 0) - 1);
		cout << n << " " << init.back() << "\n";
	}
	vector<lli> p = BerlekampMassey(init);
	init.resize(p.size());
	*/
	vector<lli> p = {187820336, 812179787, 367438184, 632561939, 314727029, 685273094, 280443822, 719556301, 847853823, 152146300, 738069702, 261930421, 268880381, 731119742, 994706153, 5293970, 61446, 999938677, 999999738, 385, 1};
	vector<lli> init = {5, 29, 159, 951, 6031, 40615, 287975, 2105087, 16023807, 124872471, 994738711, 164732759, 250001662, 985016691, 213598635, 213369543, 560810983, 897952997, 673837108, 425629536, 312478254};
	lli ans = 0;
	for(lli n = 2; n <= (1ll << 39); n <<= 1){
		ans += rec(p, init, n-1);
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}