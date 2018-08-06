#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	string a, b;
	cin >> a >> b;
	int m = a.size(), n = b.size();
	vector<vector<int>> lcs(m + 1, vector<int>(n + 1));
	for(int i = 1; i <= m; ++i){
		for(int j = 1; j <= n; ++j){
			if(a[i - 1] == b[j - 1])
				lcs[i][j] = 1 + lcs[i - 1][j - 1];
			else
				lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
		}
	}
	cout << lcs[m][n];
	return 0;
}