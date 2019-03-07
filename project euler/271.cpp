#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

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

lli extendedGcd(lli a, lli b, lli & s, lli & t){
	lli q, r0 = a, r1 = b, ri, s0 = 1, s1 = 0, si, t0 = 0, t1 = 1, ti;
	while(r1){
		q = r0 / r1;
		ri = r0 % r1, r0 = r1, r1 = ri;
		si = s0 - s1 * q, s0 = s1, s1 = si;
		ti = t0 - t1 * q, t0 = t1, t1 = ti;
	} 
	s = s0, t = t0;
	return r0;
}

lli crt(const vector<lli> & a, const vector<lli> & m){
	lli a0 = a[0] % m[0], m0 = m[0], a1, m1, s, t, d, M;
	for(int i = 1; i < a.size(); ++i){
		a1 = a[i] % m[i], m1 = m[i];
		d = extendedGcd(m0, m1, s, t);
		if((a0 - a1) % d != 0) assert(true);
		M = m0 * (m1 / d);
		a0 = a0 * t % M * (m1 / d) % M + a1 * s % M * (m0 / d) % M;
		while(a0 >= M) a0 -= M; while(a0 < 0) a0 += M;
		m0 = M;
	}
	while(a0 >= m0) a0 -= m0; while(a0 < 0) a0 += m0;
	return a0;
}

const vector<lli> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};

vector<lli> cube_root(lli m){
	vector<lli> ans;
	for(lli i = 1; i < m; ++i){
		if(i*i*i % m == 1){
			ans.push_back(i);
		}
	}
	return ans;
}

vector<vector<lli>> res(primes.size());
vector<lli> tmp(primes.size());

lli ans = 0;

void dfs(int pos){
	if(pos == primes.size()){
		ans += crt(tmp, primes);
	}else{
		for(int i = 0; i < res[pos].size(); ++i){
			tmp[pos] = res[pos][i];
			dfs(pos + 1);
			tmp[pos] = 0;
		}
	}
}

int main(){
	for(int i = 0; i < primes.size(); ++i){
		res[i] = cube_root(primes[i]);
	}
	dfs(0);
	cout << ans-1 << "\n";
	return 0;
}