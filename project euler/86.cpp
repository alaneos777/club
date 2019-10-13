#include <bits/stdc++.h>
using namespace std;

int M = 100;
int ans = 0;

void dfs(const vector<int> & t){
	int a = t[0];
	int d = t[1];
	int L = t[2];
	if(a <= M){
		cout << a << " " << d << " " << L << "\n";
		int sols = max(0, min(M, d - 1) - max({1, d - M, (d + 1) / 2}) + 1);
		ans += sols;
		dfs({1*t[0]-2*t[1]+2*t[2], 2*t[0]-1*t[1]+2*t[2], 2*t[0]-2*t[1]+3*t[2]});
		dfs({-1*t[0]+2*t[1]+2*t[2], -2*t[0]+1*t[1]+2*t[2], -2*t[0]+2*t[1]+3*t[2]});
		dfs({1*t[0]+2*t[1]+2*t[2], 2*t[0]+1*t[1]+2*t[2], 2*t[0]+2*t[1]+3*t[2]});
	}
}

int main(){
	//
	cout << ans << "\n";
	return 0;
}