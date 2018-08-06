//O(max(A_1, A_2, ..., A_k)^2 * log(n))
#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1e7 + 19;

lli linear_recurrence(vector<lli> &a, vector<lli> &x, lli k)
{
	int n = a.size();
	vector<lli> t(2 * n + 1);
	function<vector<lli>(lli)> rec = [&](lli k)
	{
		vector<lli> c(n);
		if (k < n) c[k] = 1;
		else
		{
			vector<lli> b = rec(k / 2);
			fill(t.begin(), t.end(), 0);
			for (int i = 0; i < n; ++i){
				for (int j = 0; j < n; ++j){
					t[i+j+(k&1)] += b[i]*b[j];
				}
			}
			for (int i = n; i >= 0; --i){
				for (int j = 0; j < n; ++j){
					t[i+j] += a[j]*t[i+n]%mod;
				}
			}
			for (int i = 0; i < n; ++i){
				c[i] = t[i]%mod;
			}
		}
		return c;
	};
	vector<lli> c = rec(k);
	lli ans = 0;
	for (int i = 0; i < x.size(); ++i){
		ans += c[i]*x[i];
	}
	return ans%mod;
}



lli solveProblem(int k, lli *numbers, lli n){
	int degree = *max_element(numbers, numbers + k);
	vector<lli> charPoly(degree), initial(degree);
	for(int i = 0; i < k; i++){
		charPoly[degree - numbers[i]] = 1;
	}

	initial[0] = 1;
	for(int i = 1; i < degree; i++){
		for(int j = 0; j < k; j++){
			int pos = i - numbers[j];
			if(pos >= 0){
				initial[i] += initial[pos];
			}
		}
		initial[i] %= mod;
	}

	return linear_recurrence(charPoly, initial, n);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int k; //2 <= k <= 600
	cin >> k;
	lli *numbers = new lli[k];
	for(int i = 0; i < k; i++){
		cin >> numbers[i]; //1 <= numbers[i] <= 600
	}
	lli n;
	cin >> n;
	cout << solveProblem(k, numbers, n) << "\n";
	return 0;
}