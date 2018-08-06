#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli inv(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1 != 0){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

int main(){
	ios_base::sync_with_stdio(0);
	lli m = 1000000007;
	int n;
	lli k;
	cin >> n >> k;
	vector<lli> nums(n);
	for(int i = 0; i < n; i++){
		cin >> nums[i];
	}
	vector<lli> coefs(n);
	coefs[0] = 1;
	for(int i = 1; i < n; i++){
		coefs[i] = (((coefs[i - 1] * (k + i - 1)) % m) * inv(i, m)) % m;
	}
	for(int i = 0; i < n; i++){
		lli sum = 0;
		for(int j = 0; j <= i; j++){
			sum = (sum + (coefs[j] * nums[i - j]) % m) % m;
		}
		cout << sum << " ";
	}
	cout << "\n";
	return 0;
}