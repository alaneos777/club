#include <bits/stdc++.h>
using namespace std;

vector<int> sieve(int n){
	vector<int> cnt(n+1);
	for(int i = 2; i <= n; ++i){
		if(cnt[i] == 0){
			for(int j = i; j <= n; j += i){
				cnt[j]++;
			}
		}
	}
	return cnt;
}

const auto cnt = sieve(1000);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> ans;
	for(int i = 1; i <= n; ++i){
		if(cnt[i] == 1) ans.push_back(i);
	}
	cout << ans.size() << "\n";
	for(int x : ans){
		cout << x << " ";
	}
	cout << "\n";
	return 0;
}