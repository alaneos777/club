#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

string minimum_rotation(string s){
	int n = s.size();
	string ans = s;
	for(int i = 0; i < n; ++i){
		rotate(s.begin(), s.begin()+1, s.end());
		ans = min(ans, s);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	string s;
	cin >> n >> s;
	string ans = s;
	for(int i = 0; i <= 9; ++i){
		for(char& c : s){
			c = ((c-'0') + 1) % 10 + '0';
		}
		string t = minimum_rotation(s);
		ans = min(ans, t);
	}
	cout << ans << "\n";
	return 0;
}