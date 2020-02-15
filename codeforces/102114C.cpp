#include <bits/stdc++.h>
using namespace std;

const int M = 1e5;
vector<int> phi(M+1), mu(M+1, -1);
vector<vector<int>> divs(M+1);

vector<int> cyclotomic(int n){
	if(n == 1) return {-1, 1};
	int deg = phi[n];
	vector<int> a(deg+1);
	a[0] = 1;
	for(int d : divs[n]){
		if(mu[n/d] == 0) continue;
		if(mu[n/d] == 1){
			for(int i = deg; i >= d; --i){
				a[i] -= a[i-d];
			}
		}else{
			for(int i = d; i <= deg; ++i){
				a[i] += a[i-d];
			}
		}
	}
	return a;
}

ostream&operator<<(ostream & os, const vector<int> & p){
	bool f = true;
	for(int i = p.size() - 1; i >= 0; i--){
		int pi = p[i];
		if(pi > 0){
			if(f){
				f = false;
			}else{
				os << "+";
			}
		}else if(pi < 0){
			if(f){
				os << "-";
				f = false;
			}else{
				os << "-";
			}
		}
		if(pi != 1 && pi != -1 && pi != 0){
			if(pi > 0) os << pi;
			else os << -pi;
		}else{
			if(i == 0){
				if(pi > 0) os << pi;
				else if(pi < 0) os << -pi;
			}
		}
		if(pi != 0){
			if(i == 1){
				os << "x";
			}
			else if(i > 1){
				os << "x^" << i;
			}
		}
	}
	return os;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 1; i <= M; ++i){
		for(int j = i; j <= M; j += i){
			divs[j].push_back(i);
		}
	}
	iota(phi.begin(), phi.end(), 0);
	mu[1] = 1;
	for(int i = 2; i <= M; ++i){
		if(phi[i] == i){
			for(int j = i; j <= M; j += i){
				phi[j] -= phi[j] / i;
			}
		}
		if(mu[i]){
			for(int j = 2*i; j <= M; j += i){
				mu[j] -= mu[i];
			}
		}
	}
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		int sz = phi[n] + 1;
		vector<vector<int>> pols;
		for(int d : divs[n]){
			pols.emplace_back(cyclotomic(d));
			if(pols.back().size() < sz){
				pols.back().resize(sz);
			}
			reverse(pols.back().begin(), pols.back().end());
		}
		sort(pols.begin(), pols.end());
		for(auto & pol : pols){
			reverse(pol.begin(), pol.end());
			cout << "(" << pol << ")";
		}
		cout << "\n";
	}
	return 0;
}