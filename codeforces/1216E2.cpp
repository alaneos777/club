#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int digits(lli n){
	int d = 0;
	while(n){
		d++;
		n /= 10;
	}
	return d;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli length(lli d){
	lli ans = ((9*d - 1) * power(10, d) + 1) / 9;
	return ans;
}

lli sum(lli a, lli b){
	return (b+a) * (b-a+1) / 2;
}

lli length_acum(lli n){
	lli d = digits(n);
	lli ans = 0;
	lli a = 0;
	for(lli i = 1; i <= d; ++i){
		ans += sum(max(0ll, n - (10*a + 8)), n - a) * i;
		a = 10*a + 9;
	}
	return ans;
}

lli find_super_group(lli k){
	lli l = 1, r = 1e9, m;
	while(true){
		m = (l + r) / 2;
		if(k <= length_acum(m)){
			if(k <= length_acum(m-1)){
				r = m - 1;
			}else{
				break;
			}
		}else{
			l = m + 1;
		}
	}
	return m;
}

lli find_group(lli k){
	lli l = 1, r = 18, m;
	while(true){
		m = (l + r) / 2;
		if(k <= length(m)){
			if(k <= length(m-1)){
				r = m - 1;
			}else{
				break;
			}
		}else{
			l = m + 1;
		}
	}
	return m;
}

int kth_digit(lli n, int k){
	while(true){
		int d = n % 10;
		if(k == 0) return d;
		n /= 10;
		k--;
	}
	return 0;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli k;
		cin >> k;
		lli m = find_super_group(k);
		k -= length_acum(m-1);
		lli g = find_group(k);
		k -= length(g-1);
		k--;
		lli pos = k / g + power(10, g-1);
		cout << kth_digit(pos, g - 1 - k % g) << "\n";
	}
	return 0;
}