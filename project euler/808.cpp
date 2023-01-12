#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 1e8 - 1;

lli get_rv(lli n){
	lli ans = 0;
	while(n > 0){
		int d = n%10;
		n /= 10;
		ans = ans*10 + d;
	}
	return ans;
}

lli Sqrt(lli n){
	lli L = 1, R = 1e9, ans = -1;
	while(L <= R){
		lli mid = (L+R)/2;
		if(mid*mid <= n){
			L = mid+1;
			ans = mid;
		}else{
			R = mid-1;
		}
	}
	if(ans*ans == n) return ans;
	else return -1;
}

int main(){
	vector<int> primes;
	vector<bool> is(M+1, true);
	is[0] = is[1] = false;
	for(int i = 2; i <= M; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > M) break;
			is[d] = false;
			if(i%p == 0) break;
		}
	}
	int cnt = 0;
	lli sum = 0;
	for(lli p : primes){
		lli rev = get_rv(p*p);
		lli q = Sqrt(rev);
		if(q != -1 && rev != p*p && is[q]){
			cout << ++cnt << " " << p*p << "\n";
			sum += p*p;
			if(cnt == 50) break;
		}
	}
	cout << sum << "\n";
	return 0;
}