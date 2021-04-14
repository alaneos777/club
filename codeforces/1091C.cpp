#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	/*
	Let k|n, then:
	kt = 0 mod n
	t = 0 mod n/k
	ans(k) = Sum[1 + k*t, 0 <= t < n/k] = n/k + k*(n/k)*(n/k-1)/2
	*/
	vector<int> divs;
	for(int k = 1; k*k <= n; ++k){
		if(n % k == 0){
			divs.push_back(k);
			if(n/k != k) divs.push_back(n/k);
		}
	}
	vector<lli> vals;
	for(lli k : divs){
		vals.push_back(n/k + k*(n/k)*(n/k-1)/2);
	}
	sort(vals.begin(), vals.end());
	for(lli v : vals){
		cout << v << " ";
	}
	cout << "\n";
	return 0;
}