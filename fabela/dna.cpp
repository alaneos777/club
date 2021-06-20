#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

inline int get(char c){
	if(c == 'A') return 0;
	if(c == 'T') return 1;
	if(c == 'C') return 2;
	if(c == 'G') return 3;
	return 0;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n; string s;
	cin >> n >> s;
	vector<vector<int>> cnt(4, vector<int>(n));
	for(int i = 0; i < n; ++i){
		cnt[get(s[i])][i] = 1;
	}
	for(int i = 0; i < 4; ++i){
		partial_sum(cnt[i].begin(), cnt[i].end(), cnt[i].begin());
	}
	auto sum = [&](int l, int r, int x){
		return cnt[x][r] - (l ? cnt[x][l-1] : 0);
	};
	int ans = 0;
	for(int i = 0; i < n; ++i){
		for(int j = i; j < n; ++j){
			if(sum(i, j, 0) == sum(i, j, 1) && sum(i, j, 2) == sum(i, j, 3)){
				ans++;
			}
		}
	}
	cout << ans << "\n";
	return 0;
}