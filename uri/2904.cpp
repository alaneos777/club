#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> arcs(n), acum;
	int p = 0;
	for(int & arc : arcs){
		cin >> arc;
		p += arc;
		acum.push_back(p);
	}
	if(p % 2 == 1){
		cout << "N\n";
		return 0;
	}
	int pairs = 0;
	for(int i = 0; i < n; ++i){
		int a = acum[i];
		if(a > p / 2) break;
		int b = acum[i] + p / 2;
		if(binary_search(acum.begin(), acum.end(), b)){
			pairs++;
		}
	}
	if(pairs >= 2) cout << "Y\n";
	else cout << "N\n";
	return 0;
}