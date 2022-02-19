#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		int len = 0;
		map<char, int> f;
		for(int i = 0; i < n; ++i){
			string s;
			cin >> s;
			len += s.size();
			for(char c : s){
				f[c]++;
			}
		}
		if(len % n == 0){
			len /= n;
			bool test = true;
			for(auto[_, cnt] : f){
				if(cnt % n != 0){
					test = false;
					break;
				}
			}
			if(test){
				cout << "YES\n";
			}else{
				cout << "NO\n";
			}
		}else{
			cout << "NO\n";
		}
	}
	return 0;
}