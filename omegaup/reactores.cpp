#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> costs;
vector<int> mem;
int n, k;

int countOnes(int n){
	int ans = 0;
	while(n){
		if(n & 1) ++ans;
		n >>= 1;
	}
	return ans;
}

int ans(int state){
	int turnedOn = countOnes(state);
	if(turnedOn >= k) return 0;
	int &res = mem[state];
	if(res != -1) return res;
	res = numeric_limits<int>::max();
	for(int i = 0; i < n; ++i){
		if(state & (1 << i)){
			for(int j = 0; j < n; ++j){
				if(!(state & (1 << j))){
					res = min(res, costs[i][j] + ans(state | (1 << j)));
				}
			}
		}
	}
	return res;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	costs = vector<vector<int>>(n, vector<int>(n));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cin >> costs[i][j];
		}
	}
	int initial = 0;
	char c;
	for(int i = 0; i < n; ++i){
		cin >> c;
		if(c == 'Y'){
			initial |= 1 << i;
		}
	}
	mem = vector<int>(1 << n, -1);
	cout << ans(initial) << "\n";
	return 0;
}