#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n;
	vector<lli> a(n);
	for(lli& ai : a) cin >> ai;
	cin >> k;
	vector<lli> b(k);
	for(lli& bi : b) cin >> bi;
	vector<pair<int, char>> ans;
	for(int j = 0; j < k; ++j){
		if(a.empty()){
			cout << "NO\n";
			return 0;
		}
		int i = 0;
		lli curr = 0;
		while(i < n && curr < b[j]){
			curr += a[i];
			i++;
		}
		if(curr != b[j]){
		cout << "NO\n";
			return 0;
		}
		vector<lli> v(a.begin(), a.begin() + i);
		while(v.size() > 1){
			int n = v.size();
			lli mx = *max_element(v.begin(), v.end());
			for(int l = 0; l < n; ++l){
				if(v[l] != mx) continue;
				if(l >= 1 && v[l] > v[l-1]){
					v[l] += v[l-1];
					v.erase(v.begin() + l-1);
					ans.emplace_back(j+l, 'L');
					break;
				}else if(l+1 < n && v[l] > v[l+1]){
					v[l] += v[l+1];
					v.erase(v.begin() + l+1);
					ans.emplace_back(j+l, 'R');
					break;
				}
			}
			if(v.size() == n){
				cout << "NO\n";
				return 0;
			}
		}
		a = vector<lli>(a.begin() + i, a.end());
		n = a.size();
	}
	if(a.size() > 0){
		cout << "NO\n";
	}else{
		cout << "YES\n";
		for(auto[x, y] : ans){
			cout << x+1 << " " << y << "\n";
		}
	}
	return 0;
}