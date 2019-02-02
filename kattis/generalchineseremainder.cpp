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

istream &operator>>(istream &is, __int128 & value){
	char buffer[64];
	is >> buffer;
	char *pos = begin(buffer);
	int sgn = 1;
	value = 0;
	if(*pos == '-'){
		sgn = -1;
		++pos;
	}else if(*pos == '+'){
		++pos;
	}
	while(*pos != '\0'){
		value = (value << 3) + (value << 1) + (*pos - '0');
		++pos;
	}
	value *= sgn;
	return is;
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

pair<lli, lli> crt(const vector<lli> & a, const vector<lli> & m){
	lli a0 = a[0] % m[0], m0 = m[0], a1, m1, s, t, d, M;
	for(int i = 1; i < a.size(); ++i){
		a1 = a[i] % m[i], m1 = m[i];
		d = extendedGcd(m0, m1, s, t);
		if((a0 - a1) % d != 0) return {0, 0}; //error, no solution
		M = m0 * (m1 / d);
		a0 = a0 * t % M * (m1 / d) % M + a1 * s % M * (m0 / d) % M;
		while(a0 >= M) a0 -= M; while(a0 < 0) a0 += M;
		m0 = M;
	}
	while(a0 >= m0) a0 -= m0; while(a0 < 0) a0 += m0;
	return {a0, m0};
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	lli a, n, b, m;
	cin >> t;
	while(t--){
		cin >> a >> n >> b >> m;
		auto ans = crt({a, b}, {n, m});
		if(ans.first == 0 && ans.second == 0){
			cout << "no solution\n";
		}else{
			cout << ans.first << " " << ans.second << "\n";
		}
	}
	return 0;
}