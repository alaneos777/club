#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t m){
	if(a >= m) a %= m;
	if(b >= m) b %= m;
	uint64_t c = (long double)a * b / m;
	int64_t r = (int64_t)(a * b - c * m) % (int64_t)m;
	return r < 0 ? r + m : r;
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
		if((a0 - a1) % d != 0) return {-1, -1}; //error, no solution
		M = m0 * (m1 / d);
		a0 = mul_mod(mul_mod(a0, t + M, M), m1/d, M) + mul_mod(mul_mod(a1, s + M, M), m0/d, M);
		while(a0 >= M) a0 -= M; while(a0 < 0) a0 += M;
		m0 = M;
	}
	while(a0 >= m0) a0 -= m0; while(a0 < 0) a0 += m0;
	return {a0, m0};
}

int main(){
	int tmp;
	string buses, str;
	cin >> tmp >> buses;
	stringstream ss(buses);
	int i = 0;
	vector<lli> a, m;
	while(getline(ss, str, ',')){
		if(str != "x"){
			int id = stoi(str);
			// t == -i mod id
			int rhs = -i % id;
			if(rhs < 0) rhs += id;
			a.push_back(rhs);
			m.push_back(id);
		}
		i++;
	}
	cout << crt(a, m).first << endl;
	return 0;
}