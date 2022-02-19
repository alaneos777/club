#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k, t;
	cin >> n >> m >> k >> t;
	vector<lli> waste(k);
	for(int i = 0; i < k; ++i){
		lli x, y;
		cin >> x >> y;
		--x, --y;
		waste[i] = x*m + y;
	}
	sort(waste.begin(), waste.end());
	vector<string> s = {"Carrots", "Kiwis", "Grapes"};
	for(int i = 0; i < t; ++i){
		lli x, y;
		cin >> x >> y;
		 --x, --y;
		lli pos = x*m + y;
		if(binary_search(waste.begin(), waste.end(), pos)){
			cout << "Waste\n";
		}else{
			int j = lower_bound(waste.begin(), waste.end(), pos) - waste.begin();
			lli ans = pos - j;
			cout << s[ans%3] << "\n";
		}
	}
	return 0;
}