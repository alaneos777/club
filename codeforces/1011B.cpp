#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	//ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, ai;
	cin >> n >> m;
	vector<int> a(m), freq(101);
	for(int i = 0; i < m; ++i){
		cin >> a[i];
		freq[a[i]]++;
	}
	vector<int> info;
	for(int i = 0; i <= 100; ++i){
		if(freq[i] > 0) info.push_back(freq[i]);
	}
	sort(info.begin(), info.end(), greater<int>());
	auto can = [&](int d){
		vector<int> arr = info;
		for(int i = 1; i <= n; ++i){
			if(arr[0] >= d){
				arr[0] -= d;
				sort(arr.begin(), arr.end(), greater<int>());
			}else{
				return false;
			}
		}
		return true;
	};
	int t = 0;
	for(t = 0; t <= 2000; ++t){
		if(!can(t)) break;
	}
	cout << t-1 << "\n";
	return 0;
}