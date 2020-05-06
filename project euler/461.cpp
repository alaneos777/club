#include <bits/stdc++.h>
using namespace std;
const double pi = acosl(-1);

int main(){
	double n = 10000;
	int lim = n * 1.3;
	tuple<int64_t, int64_t, int64_t, int64_t> ans;
	vector<double> e(lim+1);
	for(int k = 0; k <= lim; ++k){
		e[k] = expl(k/n) - 1;
	}
	double mini = 1e18;
	vector<tuple<double, int, int>> sums;
	for(int a = 0; a <= lim; ++a){
		for(int b = a; b <= lim; ++b){
			if(e[a] + e[b] <= pi){
				sums.emplace_back(e[a] + e[b], a, b);
			}
		}
	}
	sort(sums.begin(), sums.end());
	for(int c = 0; c <= lim; ++c){
		for(int d = c; d <= lim; ++d){
			double lhs = pi - e[c] - e[d];
			int pos = lower_bound(sums.begin(), sums.end(), make_tuple(lhs, -1, -1)) - sums.begin();
			int a, b; double sum;
			for(int i = max(0, pos - 1); i <= pos + 1 && i < sums.size(); ++i){
				tie(sum, a, b) = sums[i];
				double approx = abs(e[a] + e[b] + e[c] + e[d] - pi);
				if(approx < mini){
					mini = approx;
					ans = {a, b, c, d};
				}
			}
		}
	}
	int64_t a, b, c, d;
	tie(a, b, c, d) = ans;
	cout << a << " " << b << " " << c << " " << d << "\n";
	cout << a*a + b*b + c*c + d*d << "\n";
	return 0;
}