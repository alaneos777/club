#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	map<lli, lli> a;
	int q;
	cin >> q;
	while(q--){
		int t;
		cin >> t;
		if(t == 0){
			lli k, v;
			cin >> k >> v;
			a[k] = v;
		}else{
			lli k;
			cin >> k;
			cout << a[k] << "\n";
		}
	}
	return 0;
}