#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	lli ans = 0;
	vector<int> s;
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		while(s.size() >= 2 && s[s.size()-1] <= min(s[s.size()-2], ai)){
			ans += min(s[s.size()-2], ai);
			s.pop_back();
		}
		s.push_back(ai);
	}
	sort(s.begin(), s.end());
	for(int i = 0; i+2 < s.size(); ++i){
		ans += s[i];
	}
	cout << ans << "\n";
	return 0;
}