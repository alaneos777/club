#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int t;
	int x, k, p, q;
	cin >> t;
	while(t--){
		cin >> x >> k;
		if(x % k == 0){
			p = k;
			q = 0;
		}else{
			p = -x;
			q = x;
		}
		cout << p << " " << q << "\n";
	}
	return 0;
}