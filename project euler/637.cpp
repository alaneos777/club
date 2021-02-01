#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> getDigits(int n, int b){
	vector<int> ans;
	int b_pow = 1;
	while(n){
		int d = n%b;
		ans.push_back(d * b_pow);
		b_pow *= b;
		n /= b;
	}
	reverse(ans.begin(), ans.end());
	for(int i = 1; i < ans.size(); ++i){
		ans[i] += ans[i-1];
	}
	return ans;
}

int sumDigits(int n, int b){
	int ans = 0;
	while(n){
		ans += n%b;
		n /= b;
	}
	return ans;
}

const int N = 1e7;
const vector<int> bases = {3, 10};

int main(){
	unordered_map<int, vector<int>> b_pow;
	for(int b : bases){
		vector<int> pows(20, 1);
		for(int i = 1; i < 20; ++i){
			pows[i] = b * pows[i-1];
		}
		b_pow[b] = pows;
	}
	auto get = [&](const vector<int> & d, int b, int l, int r){
		int sum = d[r] - (l ? d[l-1] : 0);
		return sum / b_pow[b][(int)d.size()-1-r];
	};

	unordered_map<int, vector<int>> F;
	for(int b : bases){
		vector<int> steps(N+1);
		for(int n = b; n <= N; ++n){
			if(n % 10000 == 0) cout << b << " " << n << "\n";
			steps[n] = 1e9;
			int dn = sumDigits(n, b);
			if(dn < b){
				steps[n] = 1;
				continue;
			}
			if(steps[dn] == 1){
				steps[n] = 2;
				continue;
			}
			auto digits = getDigits(n, b);
			int sz = digits.size();
			for(int m = 0; m < (1 << (sz-1)); ++m){
				int prev = 0;
				int sum = 0;
				for(int i = 0; i < sz-1; ++i){
					if(m & (1 << i)){
						sum += get(digits, b, prev, i);
						prev = i+1;
					}
				}
				sum += get(digits, b, prev, sz-1);
				if(sum != n) steps[n] = min(steps[n], 1 + steps[sum]);
				if(steps[sum] <= 1) break;
			}
		}
		F[b] = steps;
	}

	lli ans = 0;
	for(lli i = 1; i <= N; ++i){
		ans += i*(F[bases[0]][i] == F[bases[1]][i]);
	}
	cout << ans << "\n";
	return 0;
}