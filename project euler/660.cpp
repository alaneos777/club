#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool mask(int n, int b, int& m){
	while(n){
		int d = n%b;
		if(m & (1 << d)) return false;
		m |= (1 << d);
		n /= b;
	}
	return true;
}

int digits(int n, int b){
	int ans = 0;
	while(n){
		ans++;
		n /= b;
	}
	return ans;
}

tuple<int, int, int> extgcd(int a, int b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extgcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

int inv(int a, int m){
	auto[d, x, _] = extgcd(a, m);
	assert(d == 1);
	if(x < 0) x += m;
	return x;
}

int main(){
	int L = 1e8;
	auto check = [&](int a, int b, int c, int base){
		int m = 0;
		bool test = mask(a, base, m);
		if(!test) return false;
		test &= mask(b, base, m);
		if(!test) return false;
		test &= mask(c, base, m);
		if(!test) return false;
		test &= (m == (1 << base) - 1);
		return test;
	};
	int ans = 0;
	function<void(int, int)> gen = [&](int m, int n){
		if(2*m*m + 3*m*n + n*n <= L){
			if((m - n) % 3 != 0){
				int a = m*m + m*n + n*n;
				int b = 2*m*n + n*n;
				int c = m*m - n*n;
				for(int base = 18; base >= 9; --base){
					int gcd = __gcd(a+b+c, base-1);
					int step = (base-1)/gcd;
					int start = 0;
					if(base&1){
						if((base-1)/2 % gcd != 0) continue;
						start = (lli)inv((a+b+c)/gcd, step) * ((base-1)/2 / gcd) % step;
					}
					for(int k = start; k*(a+b+c) <= L && digits(k*a, base) + digits(k*b, base) + digits(k*c, base) <= base; k += step){
						if(check(a*k, b*k, c*k, base)){
							cout << a*k << " " << b*k << " " << c*k << " " << base << "\n";
							ans += a*k;
						}
					}
				}
			}
			gen(2*m - n, m);
			gen(2*m + n, m);
			gen(m + 2*n, n);
		}
	};
	gen(2, 1);
	gen(3, 1);
	cout << ans << "\n";
	return 0;
}