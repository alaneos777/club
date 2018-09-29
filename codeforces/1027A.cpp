#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		string s;
		cin >> s;
		bool ans = true;
		for(int i = 0; i < n/2; ++i){
			char a = s[i], b = s[n - 1 - i];
			ans &= (a-1 == b-1 || a-1 == b+1 || a+1==b-1 || a+1==b+1);
		}
		if(ans) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}