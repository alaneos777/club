#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const int n = 50, k = 20;
const ld target = 0.02l;

auto mult(const vector<ld> & a, const vector<ld> & b){
	vector<ld> c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] += a[i]*b[j];
		}
	}
	return c;
}

ld prob(ld q){
	vector<ld> ans = {1};
	for(int i = 1; i <= 50; ++i){
		ans = mult(ans, {i/q, 1-i/q});
	}
	return ans[k];
}

int main(){
	ld l = 50, r = 60, q;
	while(abs(l-r) >= 1e-17){
		q = (l + r) / 2;
		if(prob(q) >= target){
			l = q;
		}else{
			r = q;
		}
	}
	cout << fixed << setprecision(10) << q << " " << prob(q) << "\n";
}