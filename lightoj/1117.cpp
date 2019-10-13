#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli gcd(lli a, lli b){
	lli r;
	while(b) r = a % b, a = b, b = r;
	return a;
}

lli lcm(lli a, lli b){
	lli c = b / gcd(a, b);
	lli ans = a * c;
	if(ans / a == c) return ans;
	return -1;
}

lli sgn(lli n){
	if(n > 0) return 1;
	if(n < 0) return -1;
	return 0;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		lli n; int m;
		cin >> n >> m;
		vector<lli> nums(m);
		for(lli & num : nums) cin >> num;
		vector<lli> lcms(1, 1);
		for(lli num : nums){
			int sz = lcms.size();
			for(int i = 0; i < sz; ++i){
				lli l = lcm(abs(lcms[i]), num);
				if(l != -1) lcms.push_back(-l * sgn(lcms[i]));
			}
		}
		lli ans = 0;
		for(lli l : lcms){
			ans += n / abs(l) * sgn(l);
		}
		cout << "Case " << caso << ": " << ans << "\n";
	}
	return 0;
}