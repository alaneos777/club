#include <bits/stdc++.h>
using namespace std;
using lli = long long;

lli mod = 1e9 + 7;

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, m;
	int k;
	cin >> n >> m >> k;
	if(k == -1 && (n%2!=m%2)){
		cout << "0\n";
	}else{
		cout << power(2, ((n-1)%(mod-1)) * ((m-1)%(mod-1)) % (mod-1), mod) << "\n";
	}
	return 0;
}