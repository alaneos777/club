#include <bits/stdc++.h>
using namespace std;

const int M = 12000;

vector<vector<int>> sieve(int n){
	vector<vector<int>> ans(n+1);
	for(int i = 2; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			ans[j].push_back(i);
		}
	}
	return ans;
}

const vector<vector<int>> divs = sieve(M*2);

void facts(int m, int n, vector<pair<int, int>> & sums, int acum, int len){
	if(n == 1){
		sums.emplace_back(acum, len);
		return;
	}
	for(int d : divs[n]){
		if(d <= m) facts(d, n/d, sums, d + acum, len + 1);
		else break;
	}
}

vector<vector<pair<int, int>>> getSums(int n){
	vector<vector<pair<int, int>>> sums(n+1);
	for(int i = 1; i <= n; ++i){
		facts(i, i, sums[i], 0, 0);
	}
	return sums;
}

const vector<vector<pair<int, int>>> sums = getSums(M*2);

int f(int n){
	for(int i = n+1; i <= 2*n; ++i){
		for(const auto & fact : sums[i]){
			int sum = fact.first;
			int len = fact.second;
			int rem = n - len;
			if(rem >= 0 && rem + sum == i){
				return i;
			}
		}
	}
	assert(0);
}

int main(){
	set<int> st;
	for(int i = 2; i <= M; ++i){
		int fi = f(i);
		st.insert(fi);
	}
	int ans = 0;
	for(int s : st){
		ans += s;
	}
	cout << ans << "\n";
	return 0;
}