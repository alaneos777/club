#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	char d, e;
	vector< vector<char> > mapa(n, vector<char>(n));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> mapa[i][j];
			if(i == 0 && j == 1) e = mapa[i][j];
		}
	}
	d = mapa[0][0];
	bool ans = true;
	for(int i = 0; i < n; i++){
		if(d != mapa[i][i]){
			ans = false;
			break;
		}
	}
	if(ans){
		for(int i = 0; i < n; i++){
			if(d != mapa[i][n - i - 1]){
				ans = false;
				break;
			}
		}
		if(ans){
			for(int i = 0; i < n; i++){
				if(!ans) break;
				for(int j = 0; j < n; j++){
					if(i != j && i != (n - j - 1) && (mapa[i][j] == d || mapa[i][j] != e)){
						ans = false;
						break;
					}
				}
			}
			if(ans){
				cout << "YES";
			}else{
				cout << "NO";
			}
		}else{
			cout << "NO";
		}
	}else{
		cout << "NO";
	}
	return 0;
}