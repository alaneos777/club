#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli root(lli a, int k){
	lli r = powl(a, 1.0l/k);
	lli ans = r;
	for(lli x = max(lli(0), r-1); x <= r+1; ++x){
		if(power(x, k) <= a) ans = x;
	}
	return ans;
}

bool isKthRoot(lli a, int k){
	lli r = root(a, k);
	return power(r, k) == a;
}

struct frac{
	lli x, y;
	frac(): x(0), y(1){}
	frac(lli a): x(a), y(1){}
	frac(lli a, lli b){
		if(b < 0) a = -a, b = -b;
		lli d = __gcd(abs(a), b);
		x = a/d, y = b/d;
	}
	frac operator+(const frac& f) const{
		lli d = __gcd(y, f.y);
		return frac(x*(f.y/d) + f.x*(y/d), y*(f.y/d));
	}
	frac operator-(const frac& f) const{
		lli d = __gcd(y, f.y);
		return frac(x*(f.y/d) - f.x*(y/d), y*(f.y/d));
	}
	frac operator-() const{
		return frac(-x, y);
	}
	frac operator*(const frac& f) const{
		return frac(x*f.x, y*f.y);
	}
	frac operator/(const frac& f) const{
		return frac(x*f.y, y*f.x);
	}
	frac operator^(lli n) const{
		frac ans = 1, a = *this;
		if(n < 0) a = (frac)1/a, n = -n;
		while(n){
			if(n & 1) ans = ans * a;
			n >>= 1;
			a = a * a;
		}
		return ans;
	}
	bool operator<(const frac& f) const{
		lli d = __gcd(y, f.y);
		return x*(f.y/d) < (y/d)*f.x;
	}
	bool operator==(const frac& f) const{
		return x==f.x && y==f.y;
	}
};

ostream& operator<<(ostream& os, const frac& f){
	os << f.x;
	if(f.y > 1) os << "/" << f.y;
	return os;
}

int main(){
	int k = 35;
	vector<frac> fracs;
	for(int a = 1; a <= k; ++a){
		for(int b = a+1; b <= k; ++b){
			fracs.emplace_back(a, b);
		}
	}
	sort(fracs.begin(), fracs.end());
	fracs.resize(distance(fracs.begin(), unique(fracs.begin(), fracs.end())));
	int sz = fracs.size();
	set<frac> sums;
	for(int n : {-2, -1, 1, 2}){
		for(int i = 0; i < sz; ++i){
			frac x = fracs[i];
			for(int j = i; j < sz; ++j){
				frac y = fracs[j];
				frac lhs = (x^n) + (y^n);
				if(isKthRoot(lhs.x, abs(n)) && isKthRoot(lhs.y, abs(n))){
					frac z(root(lhs.x, abs(n)), root(lhs.y, abs(n)));
					if(n < 0) z = (frac)1/z;
					if(binary_search(fracs.begin(), fracs.end(), z)){
						sums.insert(x+y+z);
					}
				}
			}
		}
	}
	frac ans = 0;
	for(frac f : sums){
		ans = ans + f;
	}
	cout << ans << "\n";
	cout << ans.x + ans.y << "\n";
	return 0;
}