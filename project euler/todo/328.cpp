#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli mem[1002][1002];
int opt[1002][1002];

ostream& operator<<(ostream& os, const vector<lli>& vec){
	os << "[";
	for(lli x : vec) os << x << " ";
	os << "]";
	return os;
}

lli f(int l, int r){
	if(l >= r){
		opt[l][r] = l;
		return 0;
	}
	lli& ans = mem[l][r];
	if(ans != -1) return ans;
	ans = 1e18;
	vector<lli> vals;
	for(int i = l; i <= r; ++i){
		lli val = i + max(f(l, i-1), f(i+1, r));
		vals.push_back(val);
		if(val < ans){
			ans = val;
			opt[l][r] = i;
		}
	}
	//cout << "opt(" << l << ", " << r << ") -> " << opt[l][r] << " " << vals << "\n";
	return ans;
}

int main(){
	memset(mem, -1, sizeof(mem));
	lli ans = 0;
	for(int i = 1; i <= 40; ++i){
		ans += f(1, i);
	}
	for(int r = 1; r <= 40; ++r){
		cout << "R = " << r << " -> [";
		for(int l = 1; l <= r; ++l){
			cout << opt[l][r] << " ";
		}
		cout << "]\n";
	}
	cout << ans << "\n";
	return 0;
}