#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli l, r;
	cin >> l >> r;
	cout << "YES\n";
	for(lli i = l; i <= r; ++i){
		cout << i;
		if((i-l) % 2 == 0) cout << " ";
		else cout << "\n";
	}
	return 0;
}