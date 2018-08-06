#include <bits/stdc++.h>
using namespace std;

int query(int y){
	int ans;
	cout << y << endl;
	cin >> ans;
	if(ans == 0) exit(0);
	return ans;
}

int main(){
	int m, n;
	cin >> m >> n;
	vector<int> seq(n);
	for(int i = 1; i <= n; ++i){
		seq[i - 1] = query(i);
	}
	int l = 1, r = m, x, i = 0;
	while(l <= r){
		int x = l + ((r - l) >> 1);
		int ans = query(x) * seq[i++];
		if(i == n) i = 0;
		if(ans == 1) l = x + 1;
		else r = x - 1;
	}
	return 0;
}