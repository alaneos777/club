#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

int main(){
	ios_base::sync_with_stdio(0);
	ull x, a;
	int n;
	string linea;
	while(cin >> x){
		vector<ull> coeficientes;
		cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, linea);
		stringstream ss;
		ss << linea;
		while(ss >> a){
			coeficientes.push_back(a);
		}
		n = coeficientes.size() - 1;
		ull ans = 0;
		for(int i = 0; i < n; i++){
			ans = ans * x + (n - i) * coeficientes[i];
		}
		cout << ans << "\n";
	}
	return 0;
}