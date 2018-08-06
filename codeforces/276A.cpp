#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;

int main(){
	lli n, k, f, t, j;
	cin >> n >> k;
	bool primero = true;
	lli ans;
	for(lli i = 0; i < n; i++){
		cin >> f >> t;
		if(t > k) j = f - (t - k);
		else j = f;
		if(primero){
			primero = false;
			ans = j;
		}else{
			if(j > ans) ans = j;
		}
	}
	cout << ans;
	return 0;
}