#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 20201227;

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

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

pair<lli, lli> discreteLogarithm(lli a, lli b, lli m){
	lli m1 = m, pw = 1, d, x, y, nonRep = 0;
	for(; (d = __gcd(a, m1)) > 1; ++nonRep, m1 /= d, pw = pw * a % m){
		if(pw == b) return {nonRep, 0}; //aperiodic solution found
	}
	d = extendedGcd(pw, m, x, y);
	if(b % d > 0) return {-1, 0}; //solution not found
	b = x * (b / d) % m;
	if(b < 0) b += m;
	lli order = m1-1;
	lli n = sqrt(order) + 1;
	lli a_n = powerMod(a, n, m1);
	unordered_map<lli, lli> firstHalf;
	pw = a_n;
	for(lli p = 1; p <= n; ++p, pw = pw * a_n % m1){
		firstHalf[pw] = p;
	}
	pw = b % m1;
	for(lli q = 0; q <= n; ++q, pw = pw * a % m1){
		if(firstHalf.count(pw)) return {nonRep + (n * firstHalf[pw] - q) % order, order}; //periodic solution found
	}
	return {-1, 0}; //solution not found
}

int main(){
	lli card_pub, door_pub;
	cin >> card_pub >> door_pub;
	lli x = discreteLogarithm(7, card_pub, mod).first;
	lli y = discreteLogarithm(7, door_pub, mod).first;
	cout << powerMod(7, x*y % (mod-1), mod) << endl;
 	return 0;
}