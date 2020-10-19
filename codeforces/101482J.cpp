#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> freq(n);
	int id = 0;
	map<string, int> mp;
	for(int i = 0; i < n; ++i){
		string s;
		cin >> s;
		if(mp.count(s) == 0){
			mp[s] = id++;
		}
		freq[mp[s]]++;
	}
	int ans = 0;
	for(int i = 0; i < n; ++i){
		string s;
		cin >> s;
		if(mp.count(s) && freq[mp[s]]){
			ans++;
			freq[mp[s]]--;
		}
	}
	cout << ans << "\n";
	return 0;
}