#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

void criba_pascal(vector< vector<ull> > & pascal, int n){
	pascal.resize(n + 1, vector<ull>());
	for(int i = 0; i <= n; i++){
		pascal[i].resize(i + 1);
		pascal[i][0] = pascal[i][i] = 1;
		for(int j = 1; j <= i / 2; j++){
			pascal[i][j] = pascal[i][i - j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	vector< vector<ull> > pascal;
	criba_pascal(pascal, 50);
	string a, b, expresion;
	int t, n;
	cin >> t;
	for(int i = 1; i <= t; i++){
		cin >> expresion;
		a = expresion.substr(1, expresion.find("+") - 1);
		b = expresion.substr(expresion.find("+") + 1, expresion.find(")") - expresion.find("+") - 1);
		stringstream(expresion.substr(expresion.find("^") + 1)) >> n;
		cout << "Case " << i << ": " << a;
		if(n > 1) cout << "^" << n;
		cout << "+";
		for(int k = 1; k < n; k++){
			cout << pascal[n][k] << "*" << a;
			if(n - k > 1) cout << "^" << (n - k);
			cout << "*" << b;
			if(k > 1) cout << "^" << k;
			cout << "+";
		}
		cout << b;
		if(n > 1) cout << "^" << n; 
		cout << "\n";
	}
	return 0;
}