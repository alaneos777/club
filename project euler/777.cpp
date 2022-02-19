#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;
using ld = long double;

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

/*const ld pi = acosl(-1);

string hsh(ld x, ld y){
	stringstream ss;
	if(x > y) swap(x, y);
	if(abs(x) < 1e-5) x = 0;
	if(abs(y) < 1e-5) y = 0;
	ss << fixed << setprecision(5) << "(" << x << ", " << y << ")";
	return ss.str();
}

map<string, int> mp;

ld norm(int a, int b, ld t){
	ld x = cos(a*t);
	ld y = cos(b*(t-pi/10));
	if(abs(abs(y) - 1) < 1e-5 || abs(abs(x) - 1) < 1e-5) return 0;
	mp[hsh(x, y)]++;
	return x*x + y*y;
}

ld f(int a, int b){
	ld ans = 0;
	for(int k1 = 0; k1 < a; ++k1){
		for(int k2 = 1; k2 < b; ++k2){
			ld term = norm(a, b, pi/a*k1 + pi/b*k2);
			ans += term;
			if(term == 0){
				cout << a << " " << b << " " << k1 << " " << k2 << "\n";
			}
		}
	}
	return ans;
}

ld d(int a, int b){
	ld ans = f(a, b) + f(b, a);
	if(a*b%10 == 0) ans /= 4;
	return ans;
}

lli D(lli a, lli b){
	if(a*b%10 == 0) return 2*a*b - 3*a - 3*b + 4;
	else return 8*a*b - 6*a - 6*b;
}*/

auto muSieve(int n){
	vector<int> primes, lp(n+1), mu(n+1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
			else mu[d] = -mu[i];
		}
	}
	return mu;
}

auto divsSieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j].push_back(i);
		}
	}
	return divs;
}

const int M = 1e6;
const auto mu = muSieve(M);
const auto divs = divsSieve(10);

lli lcm(lli a, lli b){
	return a / __gcd(a, b) * b;
}

lli lcm(lli a, lli b, lli c){
	return lcm(lcm(a, b), c);
}

lli gauss(lli n){
	return n*(n+1)/2;
}

lli P1(lli n, lli d){
	return d * (gauss(n/d) - gauss((d+1)/d - 1));
}

lli P0(lli n, lli d){
	return n/d - ((d+1)/d - 1);
}

lli S1(int n){
	lli ans = 0;
	for(int d = 1; d <= n; ++d){
		if(mu[d] == 0) continue;
		ans += mu[d] * (8*P1(n, d)*P1(n, d) - 12*P0(n, d)*P1(n, d));
	}
	return ans;
}

lli S2(int n){
	lli ans = 0;
	for(int d = 1; d <= n; ++d){
		if(mu[d] == 0) continue;
		lli term = 0;
		for(int x : divs[10]){
			int y = 10/x;
			for(int d1 : divs[y]){
				for(int d2 : divs[x]){
					lli step_a = lcm(d, x, d1);
					lli step_b = lcm(d, y, d2);
					term += mu[d1]*mu[d2] * (-6*P1(n, step_a)*P1(n, step_b) + 3*P1(n, step_a)*P0(n, step_b) + 3*P0(n, step_a)*P1(n, step_b) + 4*P0(n, step_a)*P0(n, step_b));
				}
			}
		}
		ans += mu[d] * term;
	}
	return ans;
}

int main(){
	lli ans = S1(M) + S2(M), den = 4;
	lli d = __gcd(ans, den);
	ans /= d, den /= d;
	cout << ans << "/" << den << "\n";

	ld res = ans/ld(den);
	int digits = (int)log10l(res);
	cout << fixed << setprecision(9) << res/powl(10, digits) << "e" << digits << "\n";
	
	return 0;
}