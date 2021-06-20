#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

tuple<lli, lli, lli> extgcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extgcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

lli inv(lli a, lli m){
	auto[d, x, _] = extgcd(a, m);
	assert(d == 1);
	if(x < 0) x += m;
	return x;
}

pair<lli, lli> crt(const vector<lli>& a, const vector<lli>& m){
	lli x = a[0], mod = m[0];
	for(int i = 1; i < a.size(); ++i){
		auto[d, s, t] = extgcd(mod, -m[i]);
		if((a[i] - x) % d != 0) return {-1, -1};
		lli step = m[i] / d;
		lli k = s * (((a[i] - x) / d) % step) % step;
		if(k < 0) k += step;
		x += mod*k;
		mod *= step;
	}
	return {x, mod};
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, m, x, y, vx, vy;
	cin >> n >> m >> x >> y >> vx >> vy;
	lli x0 = (-x) % n, y0 = (-y) % m;
	if(x0 < n) x0 += n;
	if(y0 < m) y0 += m;
	lli vx0 = vx % n, vy0 = vy % m;
	if(vx0 < n) vx0 += n;
	if(vy0 < m) vy0 += m;
	lli gn = __gcd(vx0, n), gm = __gcd(vy0, m);
	if(x0 % gn != 0 || y0 % gm != 0){
		cout << "-1\n";
		return 0;
	}
	vx0 /= gn, x0 /= gn; lli np = n / gn;
	vy0 /= gm, y0 /= gm; lli mp = m / gm;
	auto[t0, lcm] = crt({inv(vx0, np) * x0 % np, inv(vy0, mp) * y0 % mp}, {np, mp});
	if(t0 == -1){
		cout << "-1\n";
		return 0;
	}
	x = x + vx*t0;
	y = y + vy*t0;
	if(x / n % 2 == 0){
		cout << "0";
	}else{
		cout << n;
	}
	cout << " ";
	if(y / m % 2 == 0){
		cout << "0";
	}else{
		cout << m;
	}
	cout << "\n";
	return 0;
}