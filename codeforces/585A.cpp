#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<lli> v(n), d(n), p(n);
	vector<bool> inLine(n, true);
	for(int i = 0; i < n; ++i){
		cin >> v[i] >> d[i] >> p[i];
	}
	vector<int> ans;
	for(int i = 0; i < n; ++i){
		if(!inLine[i]) continue;
		ans.push_back(i+1);
		for(int j = i+1, subt = v[i]; j < n; ++j){
			if(!inLine[j]) continue;
			if(subt <= 0) break;
			p[j] -= subt;
			--subt;
		}
		bool change = true;
		while(change){
			change = false;
			for(int j = i+1; j < n; ++j){
				if(!inLine[j]) continue;
				if(p[j] < 0){
					inLine[j] = false;
					for(int k = j+1; k < n; ++k){
						if(!inLine[k]) continue;
						p[k] -= d[j];
						change = true;
					}
				}
			}
		}
	}
	cout << ans.size() << "\n";
	for(int ai : ans){
		cout << ai << " ";
	}
	cout << "\n";
	return 0;
}