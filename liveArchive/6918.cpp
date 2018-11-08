#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		lli a, b;
		cin >> a >> b;
		auto count = [&](lli n, int pos){
			if(n <= 0) return 0ll;
			lli ans = ((n + 1) >> (pos + 1)) << pos;
			ans += max(((n + 1) & ((1ll << (pos + 1)) - 1)) - (1ll << pos), 0ll);
			return ans;
		};
		lli AND = 0, OR = 0;
		for(int i = 0; i <= 62; ++i){
			lli countOnes = count(b, i) - count(a - 1, i);
			if(countOnes > 0){
				OR |= (1ll << i);
			}
			if(countOnes == b-a+1){
				AND |= (1ll << i);
			}
		}
		cout << "Case " << caso << ": " << OR << " " << AND << "\n";
	}
	return 0;
}