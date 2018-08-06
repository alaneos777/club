#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, ans = 0;
	cin >> n;
	vector< pair<int, int> > equipos(n);
	for(int i=0; i<n; i++){
		cin >> equipos[i].first >> equipos[i].second;
	}
	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			if(equipos[i].second == equipos[j].first) ans++;
			if(equipos[j].second == equipos[i].first) ans++;
		}
	}
	cout << ans;
	return 0;
}