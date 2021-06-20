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
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		int n;
		cin >> n;
		vector<lli> p(n), r(n);
		for(int i = 0; i < n; ++i){
			cin >> p[i] >> r[i];
		}
		auto[ans, _] = crt(r, p);
		cout << "Case " << caso << ": ";
		if(ans == -1){
			cout << "Impossible\n";
		}else{
			cout << ans << "\n";
		}
	}
	return 0;
}