#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;

int n;
ull k;
string p;
vector<double> A;

void combine(int a, int b, vector<double> & ans){
	ans.push_back(0);
	for(int i = a; i <= b; i++){
		int size = ans.size();
		for(int j = 0; j < size; j++){
			ans.push_back(ans[j] + A[i]);
		}
	}
	sort(ans.begin(), ans.end());
}

bool comp(const double & a, const double & b){
	if(abs(a - b) < 1e-9){
		return false;
	}else{
		return a < b;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k >> p;
	double log10k = log10(k);
	A.resize(n);
	for(int i = 0; i < n; i++){
		ull Ai;
		cin >> Ai;
		A[i] = log10(Ai);
	}
	ull maxSubsequences = ((ull)1 << n) - 1;
	vector<double> first, second;
	combine(0, (n - 1) / 2, first);
	combine((n - 1) / 2 + 1, n - 1, second);
	bool maxReached = false;
	int x = p.size() - 1;
	ull ans = 0;
	for(int pot = 0; pot <= x; pot++){
		ull subsequences = 0;
		if(maxReached){
			subsequences = maxSubsequences;
		}else{
			for(int i = 0; i < first.size(); i++){
				double posible = log10k - first[i] - pot;
				int j = lower_bound(second.begin(), second.end(), posible, comp) - second.begin();
				if(j < second.size()){
					if(i == 0 && j == 0) j++;
					int inc = second.size() - j;
					subsequences += inc;
				}
			}
		}
		ans += subsequences;
		if(pot == 0) ans += subsequences;
		if(subsequences == maxSubsequences) maxReached = true;
	}
	cout << ans;
	return 0;
}