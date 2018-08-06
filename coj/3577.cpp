#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0);
	int l, s, m, d, b;
	while(cin >> l >> s >> m >> d >> b){
		if(l == 0 && s == 0 && m == 0 && d == 0 && b == 0) break;
		vector<int> S(s);
		for(int i = 0; i < s; i++){
			cin >> S[i];
		}
		vector<int> M(m);
		for(int i = 0; i < m; i++){
			cin >> M[i];
		}
		vector<int> D(d);
		for(int i = 0; i < d; i++){
			cin >> D[i];
		}
		vector<int> B(b);
		for(int i = 0; i < b; i++){
			cin >> B[i];
		}
		vector<int> firstHalf;
		for(int i = 0; i < s; i++){
			for(int j = 0; j < m; j++){
				firstHalf.push_back(S[i] + M[j]);
			}
		}
		sort(firstHalf.begin(), firstHalf.end());
		lli ans = 0;
		for(int i = 0; i < d; i++){
			for(int j = 0; j < b; j++){
				lli found = upper_bound(firstHalf.begin(), firstHalf.end(), l - (D[i] + B[j])) - firstHalf.begin();
				ans += found;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}