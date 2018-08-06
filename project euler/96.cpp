#include <bits/stdc++.h>
using namespace std;

int sum = 0;

void print(vector<vector<int>> & tablero){
	/*for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			cout << tablero[i][j];
		}
		cout << "\n";
	}*/
	int ans = 100*tablero[0][0]+10*tablero[0][1]+tablero[0][2];
	//cout << ans << "\n\n";
	sum += ans;
}

void solve(vector<vector<int>> & tablero, int pos){
	if(pos == 81){
		print(tablero);
		return;
	}
	int x = pos / 9, y = pos % 9;
	if(tablero[x][y] == 0){
		vector<int> noPosibles(10);
		for(int j = 0; j < 9; j++){
			noPosibles[tablero[x][j]]++;
		}
		for(int i = 0; i < 9; i++){
			noPosibles[tablero[i][y]]++;
		}
		for(int i = (x / 3) * 3; i < (x / 3 + 1) * 3; i++){
			for(int j = (y / 3) * 3; j < (y / 3 + 1) * 3; j++){
				noPosibles[tablero[i][j]]++;
			}
		}
		for(int v = 1; v <= 9; v++){
			if(noPosibles[v] == 0){
				tablero[x][y] = v;
				solve(tablero, pos + 1);
				tablero[x][y] = 0;
			}
		}
	}else{
		solve(tablero, pos + 1);
	}
}

int main(){
	clock_t begin = clock();
	ifstream in("p096_sudoku.txt");
	string str;
	int n;
	while(in >> str >> n){
		vector<vector<int>> tablero(9, vector<int>(9));
		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 9; j++){
				char xi;
				in >> xi;
				tablero[i][j] = xi - '0';
			}
		}
		//cout << str << " " << n << "\n";
		solve(tablero, 0);
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Total: " << sum << "\n";
	cout << fixed << setprecision(4) << elapsed_secs << "s";
	return 0;
}