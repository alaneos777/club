#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using poly = vector<double>;

poly operator+(const poly & a, const poly & b){
	poly c(max(a.size(), b.size()));
	for(int i = 0; i < c.size(); ++i){
		if(i < a.size()) c[i] += a[i];
		if(i < b.size()) c[i] += b[i];
	}
	return c;
}

poly operator*(const poly & a, const poly & b){
	if(a.empty() || b.empty()) return {};
	poly c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] += a[i]*b[j];
		}
	}
	return c;
}

int main(){
	vector<int> dices = {4, 6, 8, 12, 20};
	poly F = {0, 1};
	for(int d : dices){
		poly nxt = {};
		poly p(d+1, 1.0/d);
		p[0] = 0;
		for(int i = F.size()-1; i >= 0; --i){
			nxt = nxt*p + poly{F[i]};
		}
		F = nxt;
	}
	double sum_sq = 0, sum = 0;
	for(int i = 0; i < F.size(); ++i){
		sum_sq += i*i*F[i];
		sum += i*F[i];
	}
	double ans = sum_sq - sum*sum;
	cout << fixed << setprecision(4) << ans << "\n";
	return 0;
}