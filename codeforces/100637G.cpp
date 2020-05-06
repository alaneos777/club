#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	int earth = 0, alien = 0, neither = 0;
	cin.ignore();
	for(int i = 0; i < n; ++i){
		string linea, word, all;
		getline(cin, linea);
		stringstream ss(linea);
		int blue = 0, black = 0, white = 0, gold = 0;
		while(ss >> word){
			all += word;
		}
		if(all.find("blue") != string::npos) blue++;
		if(all.find("black") != string::npos) black++;
		if(all.find("white") != string::npos) white++;
		if(all.find("gold") != string::npos) gold++;
		if(blue >= 1 && black >= 1){
			earth++;
		}else if(white >= 1 && gold >= 1){
			alien++;
		}else{
			neither++;
		}
	}
	cout << fixed << setprecision(8) << (double)earth / n * 100 << "\n" << (double)alien / n * 100 << "\n" << (double)neither / n * 100 << "\n";
	return 0;
}