#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const int N = 15;

vector<ld> operator*(const vector<ld> & a, const vector<ld> & b){
	vector<ld> c(a.size() + b.size());
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] += a[i]*b[j];
		}
	}
	return c;
}

ld f(int n){
	vector<ld> f = {1};
	for(int i = 1; i <= n; ++i){
		ld p = 1.0l / (i + 1);
		f = f * vector<ld>{1 - p, 0, p};
	}
	ld ans = 0;
	for(int i = 1; i + n < f.size(); ++i){
		ans += f[i + n];
	}
	return ans;
}

int main(){
	cout << int(1.0l / f(N)) << "\n";
	return 0;
}