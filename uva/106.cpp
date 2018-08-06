#include <bits/stdc++.h>

using namespace std;

typedef long long int ull;

int main(){
	ios_base::sync_with_stdio(0);
	ull N;
	while(cin >> N){
		ull limit1 = sqrt(((double)N)/2);
		ull cont = 0, contp = N;
		vector<bool> numeros(N + 1, false);
		for(ull n = 1; n <= limit1; n++){
			ull limit2 = sqrt(N - n*n);
			for(ull m = n + 1; m <= limit2; m+=2){
				if(__gcd(m, n) == 1){
					ull x = m*m - n*n;
					ull y = 2*m*n;
					ull z = m*m + n*n;
					cont++;
					for(ull i = x, j = y, k = z; i <= N && j <= N && k <= N; i += x, j += y, k += z){
						if(!numeros[i]) --contp;
						if(!numeros[j]) --contp;
						if(!numeros[k]) --contp;
						numeros[i] = numeros[j] = numeros[k] = true;
					}
				}
			}
		}
		cout << cont << " " << contp << "\n";
	}
	return 0;
}