#include <bits/stdc++.h>
using namespace std;
using lli = long long;

lli gcd(lli a, lli b){
	lli r;
	while(b != 0) r = a % b, a = b, b = r;
	return a;
}

lli multMod(lli a, lli b, lli n){
	lli ret = a * b - (lli)((long double)a * b / n + 0.5) * n;
	return ret < 0 ? ret + n : ret;
}

lli getFactor(lli n){
	static lli seq[1000001];
	while(1) {
		lli x = rand() % n, y = x, c = rand() % n;
		lli *px = seq, *py = seq, tim = 0, prd = 1;
		while(1) {
			*py++ = y = multMod(y, y, n) + c;
			*py++ = y = multMod(y, y, n) + c;
			if((x = *px++) == y) break;
			lli tmp = prd;
			prd = multMod(prd, abs(y - x), n);
			if(!prd) return gcd(tmp, n);
			if((++tim) == 25) {
				if((prd = gcd(prd, n)) > 1 && prd < n) return prd;
				tim = 0;
			}
		}
		if(tim && (prd = gcd(prd, n)) > 1 && prd < n) return prd;
	}
}

lli mod = 998244353;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	srand(time(0));
	unordered_map<lli, int> prod;
	prod.reserve(1024); prod.max_load_factor(0.25);
	int n;
	cin >> n;
	while(n--){
		lli ai;
		cin >> ai;
		lli r = round(sqrt(sqrt(ai)));
		lli s = round(cbrt(ai));
		lli t = round(sqrt(ai));
		if(r*r*r*r == ai){
			prod[r] += 4;
		}else if(s*s*s == ai){
			prod[s] += 3;
		}else if(t*t == ai){
			prod[t] += 2;
		}else{
			lli a = ai;
			for(auto & f : prod){
				if(a == 1) break;
				int pot = 0;
				while(a % f.first == 0){
					++pot;
					a /= f.first;
				}
				if(pot) prod[f.first] += pot;
			}
			if(a == ai){
				lli f;
				do{
					f = getFactor(ai);
				}while(f == ai);
				prod[f]++;
				prod[ai / f]++;
			}else if(a > 1){
				prod[a]++;
			}
		}
	}
	lli ans = 1;
	for(auto & f : prod){
		ans = ans * (f.second + 1) % mod;
	}
	cout << ans << "\n";
	return 0;
}