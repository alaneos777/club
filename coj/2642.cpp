#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		string n;
		cin >> n;
		int ans = 0;
		int alt = 1;
		for(char c : n){
			ans += (c - '0') * alt;
			alt *= -1;
		}
		if(ans%3 == 0) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}