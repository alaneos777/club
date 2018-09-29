#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		unordered_map<int, int> freq;
		for(int i = 0; i < n; ++i){
			int s;
			cin >> s;
			freq[s]++;
		}
		vector<lli> sticks;
		for(auto & p : freq){
			int rep = p.second / 2;
			for(int j = 1; j <= rep; ++j){
				sticks.push_back(p.first);
			}
		}
		sort(sticks.begin(), sticks.end());
		n = sticks.size();
		int idx = -1;
		lli num = 0, den = 1;
		for(int i = 0; i < n - 1; i++){
			lli a = sticks[i + 1], b = sticks[i];
			if(idx == -1 || (a*a + b*b)*den < a*b*num){
				num = a*a + b*b, den = a*b;
				idx = i;
			}
		}
		cout << sticks[idx] << " " << sticks[idx] << " " << sticks[idx+1] << " " << sticks[idx+1] << "\n";
	}
	return 0;
}