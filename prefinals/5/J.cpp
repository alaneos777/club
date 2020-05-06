#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli k;
		cin >> k;
		k--;
		int cnt = 0;
		while(k){
			if(k & 1) cnt++;
			k >>= 1;
		}
		cout << (1ll << cnt) << "\n";
	}
	return 0;
}