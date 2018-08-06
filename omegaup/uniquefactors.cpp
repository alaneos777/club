#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct HASH{
  size_t operator()(const pair<int,int>&x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
  }
};

unordered_map<pair<int, int>, lli, HASH> mem;

lli g(int m, int n){
	if(m == 1 && n == 1) return 1;
	if(m == 1) return 0;
	if(n == 1) return 1;
	if(mem.count({m, n})) return mem[{m, n}];
	lli ans = 0;
	int l = sqrt(n);
	for(int i = 1; i <= l; ++i){
		if(n % i == 0){
			lli a = i, b = n / i;
			if(a <= m) ans += g(a, b);
			if(a != b && b <= m) ans += g(b, a);
		}
	}
	return mem[{m, n}] = ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	mem.reserve(1024);
	mem.max_load_factor(0.25);
	int n;
	cin >> n;
	cout << g(n, n) - 1;
	return 0;
}