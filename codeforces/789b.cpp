#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli b1, q, l;
	int m;
	cin >> b1 >> q >> l >> m;
	set<int> a;
	for(int i = 0; i < m; ++i){
		int ai;
		cin >> ai;
		a.insert(ai);
	}
	lli b = b1;
	int cnt = 0, total = 0;
	while(abs(b) <= l && total < 1000){
		if(a.count(b) == 0) cnt++;
		b = b * q;
		total++;
	}
	if(total == 1000){
		if(cnt <= 2){
			cout << cnt << "\n";
		}else{
			cout << "inf\n";
		}
	}else{
		cout << cnt << "\n";
	}
	return 0;
}
