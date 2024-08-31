#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli f(lli n, lli k){
	lli d = n-k;
	lli sum = n;
	int pos = 0;
	while(d){
		if(d&1){
			n -= 1ll<<pos;
			sum += n;
		}
		pos++;
		d >>= 1;
	}
	assert(n == k);
	return sum;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout << f(1e17, powl(9, 17)) << "\n";
	return 0;
}