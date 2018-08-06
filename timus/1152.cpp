#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int n, sup;
vector<int> arr, dmg, pre;
int inf = 1 << 29;

int ans(int init){
	if(init == 0) return 0;
	if(pre[init] == -1){
		int ret = inf;
		for(int i = 0; i < n; ++i){
			int next = init;
			for(int j = 0; j < 3; ++j){
				int pos = (i + j) % n;
				next &= ~(1 << pos);
			}
			if(next != init){
				ret = min(ret, dmg[next] + ans(next));
			}
		}
		pre[init] = ret;
	}
	return pre[init];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	arr.resize(n);
	for(int i = 0; i < n; ++i){
		cin >> arr[i];
	}
	sup = 1 << n;
	dmg.push_back(0);
	pre.resize(sup, -1);
	pre[0] = 0;
	for(int & v : arr){
		int size = dmg.size();
		for(int i = 0; i < size; ++i){
			dmg.push_back(v + dmg[i]);
		}
	}
	cout << ans(sup - 1);
	return 0;
}