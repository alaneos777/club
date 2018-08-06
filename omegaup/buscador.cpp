#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	string search, word;
	cin >> search;
	int t, m = search.size(), n;
	cin >> t;
	vector<string> words(t);
	int lcs_max = -1, len, pos;
	for(int p = 0; p < t; ++p){
		cin >> word;
		n = word.size();
		words[p] = word;
		vector<vector<int>> lcs(m + 1, vector<int>(n + 1));
		for(int i = 1; i <= m; ++i){
			for(int j = 1; j <= n; ++j){
				if(search[i - 1] == word[j - 1])
					lcs[i][j] = 1 + lcs[i - 1][j - 1];
				else
					lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
			}
		}
		if(lcs[m][n] > lcs_max){
			lcs_max = lcs[m][n];
			len = n;
			pos = p;
		}else if(lcs[m][n] == lcs_max){
			if(n < len){
				len = n;
				pos = p;
			}
		}
	}
	cout << words[pos];
	return 0;
}