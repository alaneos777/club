#include <bits/stdc++.h>
using namespace std;
using lli = long long;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s;
	while(cin >> s){
		lli ans = 0;
		for(int i = 0; i < s.size(); ++i){
			if('0' <= s[i] && s[i] <= '9'){
				vector<lli> acum = {1, 0, 0};
				int sum = 0;
				while('0' <= s[i] && s[i] <= '9'){				
					int d = s[i] - '0';
					sum = (sum + d) % 3;
					ans += acum[sum];
					acum[sum]++;
					i++;
				}
				i--;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}