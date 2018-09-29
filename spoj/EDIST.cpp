#include <bits/stdc++.h>
using namespace std;

int LevenshteinDistance(string & a, string & b){
	int m = a.size(), n = b.size();
	vector<vector<int>> aux(m + 1, vector<int>(n + 1));
	for(int i = 1; i <= m; ++i)
		aux[i][0] = i;
	for(int j = 1; j <= n; ++j)
		aux[0][j] = j;
	for(int j = 1; j <= n; ++j)
		for(int i = 1; i <= m; ++i)
			aux[i][j] = min({aux[i-1][j] + 1, aux[i][j-1] + 1, aux[i-1][j-1] + (a[i-1] != b[j-1])});
	return aux[m][n];
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		string a, b;
		cin >> a >> b;
		cout << LevenshteinDistance(a, b) << "\n";
	}
	return 0;
}