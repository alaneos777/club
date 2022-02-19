#include <bits/stdc++.h>
using namespace std;
using lli = int;

struct frac{
	lli x, y;
	frac(): x(0), y(1){}
	frac(lli a): x(a), y(1){}
	frac(lli a, lli b){
		lli d = __gcd(a, b);
		x = a/d, y = b/d;
	}
	frac operator+(const frac& f) const{
		return frac(x*f.y + y*f.x, y*f.y);
	}
	frac operator*(const frac& f) const{
		return frac(x*f.x, y*f.y);
	}
	frac operator/(const frac& f) const{
		return frac(x*f.y, y*f.x);
	}
	bool operator<(const frac& f) const{
		return x*f.y < y*f.x;
	}
	bool operator==(const frac& f) const{
		return x == f.x && y == f.y;
	}
};

namespace std{
	template<>
	struct hash<frac>{
		size_t operator()(const frac& f) const{
			return hash<double>()((double)f.x / (double)f.y);
		}
	};
}

unordered_set<frac> mem[50];
unordered_set<frac> gen(int n){
	if(n == 1) return {1};
	unordered_set<frac>& ans = mem[n];
	if(!ans.empty()) return ans;
	for(int sz = 1; 2*sz <= n; ++sz){
		for(frac x : gen(sz)){
			for(frac y : gen(n - sz)){
				ans.insert(x + y);
				ans.insert((x*y) / (x+y));
			}
		}
	}
	return ans;
}

int main(){
	unordered_set<frac> ans;
	for(int n = 1; n <= 18; ++n){
		for(frac x : gen(n)){
			ans.insert(x);
		}
	}
	cout << ans.size() << "\n";
	return 0;
}