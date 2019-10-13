#include <bits/stdc++.h>
using namespace std;
using lli = int;

struct fraccion{
	lli num, den;
	fraccion(){
		num = 0, den = 1;
	}
	fraccion(lli x, lli y){
		if(y < 0)
			x *= -1, y *=-1;
		lli d = __gcd(abs(x), abs(y));
		num = x/d, den = y/d;
	}
	fraccion(lli v){
		num = v;
		den = 1;
	}
	fraccion operator+(const fraccion& f) const{
		lli d = __gcd(den, f.den);
		return fraccion(num*(f.den/d) + f.num*(den/d), den*(f.den/d));
	}
	fraccion operator-() const{
		return fraccion(-num, den);
	}
	fraccion operator-(const fraccion& f) const{
		return *this + (-f);
	}
	fraccion operator*(const fraccion& f) const{
		return fraccion(num*f.num, den*f.den);
	}
	bool operator==(const fraccion& f) const{
		lli d = __gcd(den, f.den);
		return (num*(f.den/d) == (den/d)*f.num);
	}
	fraccion operator/(const fraccion& f) const{
		if(f == 0) return -1;
		return fraccion(num*f.den, den*f.num);
	}
	bool operator <(const fraccion& f) const{
        lli d = __gcd(den, f.den);
        return (num*(f.den/d) < (den/d)*f.num);
    }
};

function<fraccion(fraccion, fraccion)> f[8] = {
	[&](fraccion a, fraccion b){return a+b;},
	[&](fraccion a, fraccion b){return b+a;},
	[&](fraccion a, fraccion b){return a-b;},
	[&](fraccion a, fraccion b){return b-a;},
	[&](fraccion a, fraccion b){return a*b;},
	[&](fraccion a, fraccion b){return b*a;},
	[&](fraccion a, fraccion b){return a/b;},
	[&](fraccion a, fraccion b){return b/a;}
};

int solve(vector<fraccion> arr){
	set<int> bucket;
	sort(arr.begin(), arr.end());
	do{
		for(int i = 0; i < 8; ++i){
			for(int j = 0; j < 8; ++j){
				for(int k = 0; k < 8; ++k){
					fraccion f1 = f[i](f[j](arr[0], arr[1]), f[k](arr[2], arr[3]));
					if(!(f1 == -1) && f1.den == 1 && f1.num >= 1){
						bucket.insert(f1.num);
					}
					fraccion f2 = f[i](f[j](f[k](arr[0], arr[1]), arr[2]), arr[3]);
					if(!(f2 == -1) && f2.den == 1 && f2.num >= 1){
						bucket.insert(f2.num);
					}
				}
			}
		}
	}while(next_permutation(arr.begin(), arr.end()));
	int curr = 0;
	for(int n : bucket){
		if(curr + 1 != n){
			return curr;
		}
		curr = n;
	}
	return curr;
}

int main(){
	int n = 0;
	vector<int> ans;
	for(int a = 0; a <= 9; ++a){
		for(int b = a+1; b <= 9; ++b){
			for(int c = b+1; c <= 9; ++c){
				for(int d = c+1; d <= 9; ++d){
					int tmp = solve({a, b, c, d});
					if(tmp > n){
						n = tmp;
						ans = {a, b, c, d};
					}
				}
			}
		}
	}
	cout << ans[0] << ans[1] << ans[2] << ans[3] << "\n";
	cout << n << "\n";
	return 0;
}