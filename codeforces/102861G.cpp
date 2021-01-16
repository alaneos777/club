#include <bits/stdc++.h>
using namespace std;

int mat[10][10];

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	bool valid = true;
	while(n--){
		int d, l, r, c;
		cin >> d >> l >> r >> c;
		--r, --c;
		if(d == 0){
			for(int j = c; j < c+l; ++j){
				if(j == 10){
					valid = false;
					break;
				}
				mat[r][j]++;
			}
		}else{
			for(int i = r; i < r+l; ++i){
				if(i == 10){
					valid = false;
					break;
				}
				mat[i][c]++;
			}
		}
	}
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 10; ++j){
			valid &= (mat[i][j] <= 1);
		}
	}
	if(valid) cout << "Y\n";
	else cout << "N\n";
	return 0;
}