#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	if(fopen("alignment.in", "r")){
		freopen("alignment.in", "r", stdin);
		freopen("alignment.out", "w", stdout);
	}
	string str;
	vector<vector<string>> lines;
	int m = 0, n = 0;
	while(getline(cin, str)){
		string word;
		stringstream ss(str);
		vector<string> line;
		while(ss >> word){
			line.push_back(word);
		}
		lines.push_back(line);
		m++;
		n = max(n, (int)line.size());
	}
	vector<int> col_spaces(n);
	for(int j = 0; j < n; ++j){
		int spaces = 0;
		for(int i = 0; i < m; ++i){
			if(j < lines[i].size()){
				spaces = max(spaces, (int)lines[i][j].size());
			}
		}
		col_spaces[j] = spaces;
	}
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < lines[i].size(); ++j){
			if(j) cout << " ";
			if(j+1 < lines[i].size()){
				cout << left << setw(col_spaces[j]) << lines[i][j];
			}else{
				cout << lines[i][j];
			}
		}
		cout << "\n";
	}
	return 0;
}