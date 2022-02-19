#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for(int& ai : a){
		cin >> ai;
	}
	unordered_map<int, int> freq;
	map<int, multiset<int>> mp;
	auto add = [&](int ai){
		int& f = freq[ai];
		if(f > 0){
			mp[f].erase(mp[f].find(ai));
			if(mp[f].size() == 0) mp.erase(f);
		}
		f++;
		mp[f].insert(ai);
	};
	auto erase = [&](int ai){
		int& f = freq[ai];
		mp[f].erase(mp[f].find(ai));
		if(mp[f].size() == 0) mp.erase(f);
		f--;
		if(f > 0){
			mp[f].insert(ai);
		}
	};
	auto ans = [&](){
		if(mp.begin()->first != 1) return string("Nothing");
		return to_string(*(mp.begin()->second.rbegin()));
	};
	for(int i = 0; i < k; ++i){
		add(a[i]);
	}
	cout << ans() << "\n";
	for(int i = 1; i+k-1 <= n-1; ++i){
		erase(a[i-1]);
		add(a[i+k-1]);
		cout << ans() << "\n";
	}
	return 0;
}