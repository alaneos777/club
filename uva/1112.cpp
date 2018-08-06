#include <bits/stdc++.h>
using namespace std;

int inf = 1e9;

int main(){
	ios_base::sync_with_stdio(0);
	int casos, n, e, T, m, a, b, t;
	cin >> casos;
	while(casos--){
		int ans = 0;
		cin >> n >> e >> T >> m;
		--e;
		vector< vector<int> > mapa(n, vector<int>(n, inf));
		for(int i = 0; i < n; ++i){
			mapa[i][i] = 0;
		}
		for(int i = 0; i < m; ++i){
			cin >> a >> b >> t;
			mapa[--a][--b] = t;
		}
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				for(int k = 0; k < n; ++k){
					mapa[j][k] = min(mapa[j][k], mapa[j][i] + mapa[i][k]);
				}
			}
		}
		for(int i = 0; i < n; ++i){
			if(mapa[i][e] <= T){
				++ans;
			}
		}
		cout << ans << "\n";
		if(casos){
			cout << "\n";
		}
	}
	return 0;
}