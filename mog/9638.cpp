#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string b;
	int s;
	cin >> b >> s;
	int n = b.size();
	vector<int> pos;
	for(int i = 0; i < n+s-1; ++i){
		if(b[i%n] == 'E'){
			pos.push_back(i);
		}
	}
	lli ans = 0;
	for(int i = 0; i < n; ++i){
		if(b[i] == 'E'){
			ans += s;
		}else if(!pos.empty()){
			int k = *lower_bound(pos.begin(), pos.end(), i);
			ans += max(0, s - abs(i - k));
		}
	}
	cout << ans << "\n";
	return 0;
}