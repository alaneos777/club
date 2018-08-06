#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int ull;

int main(){
	ios_base::sync_with_stdio(0);
	int t;
	string cad;
	cin >> t;
	vector<ull> fact(21, 1);
	for(int i = 1; i <= 20; i++){
		fact[i] = fact[i - 1] * i;
	}
	for(int i = 1; i <= t; i++){
		cin >> cad;
		int n = cad.size();
		vector<int> frecuencias(26, 0);
		for(char & c : cad){
			frecuencias[c - 'A']++;
		}
		ull ans = fact[n];
		for(int j = 0; j < 26; ++j){
			ans /= fact[frecuencias[j]];
		}
		cout << "Data set " << i << ": " << ans << "\n";
	}
	return 0;
}