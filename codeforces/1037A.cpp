#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli LOG2(lli n){
	lli ans = 0;
	while(n >>= 1) ans++;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n;
	cin >> n;
	cout << LOG2(n)+1 << "\n";
	return 0;
}