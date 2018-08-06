#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		switch(i % 4){
			case 1: case 3:{
				for(int j = 1; j <= m; j++) cout << "#";
					break;
			}
			case 0:{
				cout << "#";
				for(int j = 2; j <= m; j++) cout << ".";
					break;
			}
			case 2:{
				for(int j = 2; j <= m; j++) cout << ".";
				cout << "#";
				break;
			}
		}
		if(n != i) cout << "\n";
	}
	return 0;
}