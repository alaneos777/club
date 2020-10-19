#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using lli = int64_t;
using LLI = __int128_t;
using comp = complex<ld>;
const ld pi = acosl(-1);

lli inverse(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

pair<lli, lli> linear(lli a, lli b, lli m){
	if(a == 0 && b == 0){
		return {0, 1};
	}
	lli g = __gcd(a, b);
	a /= g, b /= g, m /= __gcd(m, g);
	if(__gcd(a, m) != 1) return {-1, 1};
	return {(LLI)inverse(a, m) * b % m, m};
}

LLI powerMod(LLI a, LLI b, LLI m){
	LLI ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

bool isPrime(lli n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) continue;
		int k = 0;
		for(; k < s; ++k){
			m = (LLI)m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

lli getFactor(lli n){
	lli a = 1 + rand() % (n - 1), b = 1 + rand() % (n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = (LLI)x * ((LLI)x + b) % n + a;
		y = (LLI)y * ((LLI)y + b) % n + a;
		y = (LLI)y * ((LLI)y + b) % n + a;
		d = __gcd(abs(x - y), n);
	}
	return d;
}

map<lli, int> fact;
void factorice(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrime(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorice(f, false);
		for(auto & it : fact){
			while(n % it.first == 0){
				n /= it.first;
				++it.second;
			}
		}
	}
	if(n > 1) ++fact[n];
}

lli resultant(int a, int b){
	comp x1 = -(ld)a - cbrtl(b);
	comp x2 = -(ld)a + polar(1.0l, pi/3) * cbrtl(b);
	comp x3 = -(ld)a + polar(1.0l, 5*pi/3) * cbrtl(b);
	comp res = (x1*x1*x1 + (ld)b) * (x2*x2*x2 + (ld)b) * (x3*x3*x3 + (ld)b);
	return (lli)roundl(abs(res.real())); //can also be a^7 + 27ab^2
}

void getDivs(lli n, function<void(const map<lli, int>&, lli)> callback){
	factorice(n);
	map<lli, int> curr;
	function<void(map<lli, int>::iterator, lli)> go = [&](map<lli, int>::iterator it, lli d){
		if(it == fact.end()){
			callback(curr, d);
		}else{
			auto it2 = it; ++it2;
			lli p; int a;
			tie(p, a) = *it;
			lli p_pow = 1;
			for(int i = 0; i <= a; ++i){
				go(it2, d * p_pow);
				p_pow *= p;
				curr[p] = i+1;
			}
			curr.erase(p);
		}
	};
	go(fact.begin(), 1);
}

set<lli> cuberoot(lli n, lli p){
	if(n == 0) return {0};
	if(p == 3) return {(lli)n};
	if(p % 3 == 2) return {(lli)powerMod(n, (2*p-1)/3, p)};
	if(powerMod(n, (p-1)/3, p) != 1) return {};
	int s = 0;
	lli t = p-1, s_pow = 1;
	while(t % 3 == 0){
		s++;
		s_pow *= 3;
		t /= 3;
	}
	s_pow /= 3;
	lli b = p-2;
	while(powerMod(b, (p-1)/3, p) == 1){
		b--;
	}
	lli g = powerMod(b, (p-1)/3, p);
	lli c = powerMod(b, t, p), r = powerMod(n, t, p);
	lli c1 = powerMod(c, s_pow, p), h = 1;
	c = powerMod(c, p-2, p);
	for(int i = 1; i < s; ++i){
		s_pow /= 3;
		lli d = powerMod(r, s_pow, p);
		if(d == c1){
			h = (LLI)h * c % p;
			r = (LLI)r * powerMod(c, 3, p) % p;
		}else if(d != 1){
			h = (LLI)h * powerMod(c, 2, p) % p;
			r = (LLI)r * powerMod(c, 6, p) % p;
		}
		c = powerMod(c, 3, p);
	}
	lli k = (t-1)%3 == 0 ? (t-1)/3 : (t+1)/3;
	r = (LLI)h * powerMod(n, k, p) % p;
	if((t-1)%3 == 0){
		r = powerMod(r, p-2, p);
	}
	assert(powerMod(r, 3, p) == n);
	return {r, lli((LLI)r*g%p), lli((LLI)r*g%p*g%p)};
}

lli solveSystem(lli a, lli b, const map<lli, int> & f, lli d){
	vector<vector<pair<lli, lli>>> eqns;
	for(const auto & par : f){
		lli p; int e;
		tie(p, e) = par;
		set<lli> roots = cuberoot(((p - b) % p + p) % p, p);
		for(lli r : roots){
			assert(powerMod(r, 3, p) == ((p - b) % p + p) % p);
		}
		lli p_pow = p;
		for(int i = 2; i <= e; ++i){
			p_pow *= p;
			set<lli> New;
			for(lli r : roots){
				LLI lhs = (LLI)3*r*r * (p_pow / p);
				LLI rhs = -((LLI)r*r*r + b);
				auto tmp = linear(lhs % p_pow, (rhs % p_pow + p_pow) % p_pow, p_pow);
				lli k = tmp.first;
				if(k == -1) continue;
				while(k < p){
					New.insert((r + (LLI)k * (p_pow/p) % p_pow) % p_pow);
					k += tmp.second;
				}
			}
			roots = New;
		}
		vector<pair<lli, lli>> eqn;
		for(lli r : roots){
			eqn.emplace_back(r, p_pow);
		}
		eqns.emplace_back(eqn);
	}
	vector<lli> sols;
	function<void(int, lli, lli)> dfs = [&](int pos, lli a0, lli m0){
		if(pos == eqns.size()){
			if(a0 != -1) sols.push_back(a0);
		}else{
			for(const auto & par : eqns[pos]){
				lli ai, mi;
				tie(ai, mi) = par;
				if(pos == 0){
					dfs(pos+1, ai, mi);
				}else{
					lli prod = m0 * mi;
					dfs(pos+1, ((LLI)a0 * mi % prod * inverse(mi, m0) % prod + (LLI)ai * m0 % prod * inverse(m0, mi) % prod) % prod, prod);
				}
			}
		}
	};
	dfs(0, -1, -1);
	sort(sols.begin(), sols.end());
	lli ans = -1;
	for(int i = 0; i < sols.size(); ++i){
		lli n = sols[i];
		if(sols[(i+1) % sols.size()] == (n+a) % d && __gcd((LLI)n*n*n + b, (LLI)(n+a)*(n+a)*(n+a) + b) == d){
			ans = n;
			break;
		}
	}
	return ans;
}

lli G(int a, int b){
	lli res = resultant(a, b);
	lli d_max = 0, ans = -1;
	getDivs(res, [&](const map<lli, int> & f, lli d){
		lli n = solveSystem(a, b, f, d);
		if(n != -1 && d > d_max){
			ans = n;
		}
	});
	assert(ans != -1);
	return ans;
}

int main(){
	srand(time(0));
	int m = 18, n = 1900;
	lli ans = 0;
	for(int a = 1; a <= m; ++a){
		for(int b = 1; b <= n; ++b){
			lli tmp = G(a, b);
			ans += tmp;
		}
	}
	cout << ans << "\n";
	return 0;
}