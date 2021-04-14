#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> ten(10);
	ten[0] = 1;
	for(int i = 1; i < 10; ++i){
		ten[i] = ten[i-1] * 10;
	}
	int t;
	cin >> t;
	while(t--){
		int a, b, c;
		cin >> a >> b >> c;
		// gcd(x, y) = z
		// 10^(a-1) <= x <= 10^a-1
		// 10^(b-1) <= y <= 10^b-1
		// 10^(c-1) <= z <= 10^c-1
		// x = s*z , y = t*z , gcd(s, t) = 1
		int z = ten[c-1];
		// ceil(10^(a-1)/z) <= s <= floor((10^a-1)/z)
		// ceil(10^(b-1)/z) <= t <= floor((10^b-1)/z)
		int ls = (ten[a-1] + z-1) / z, rs = (ten[a] - 1) / z;
		int lt = (ten[b-1] + z-1) / z, rt = (ten[b] - 1) / z;
		int x, y;
		bool found = false;
		for(int s = ls; s <= rs; ++s){
			if(found) break;
			for(int t = lt; t <= rt; ++t){
				if(__gcd(s, t) == 1){
					x = s*z, y = t*z;
					found = true;
					break;
				}
			}
		}
		cout << x << " " << y << "\n";
	}
	return 0;
}