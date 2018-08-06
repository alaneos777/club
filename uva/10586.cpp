#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

int grado(vector<ull> & polinomio){
	return polinomio.size() - 1;
}

void quitar_ceros(vector<ull> & polinomio){
	while(!polinomio.empty() && polinomio.back() == 0){
		polinomio.pop_back();
	}
	if(polinomio.empty()){
		polinomio.push_back(0);
	}
}

void dividir(vector<ull> & R, int k){
	ull q;
	int g;
	while(grado(R) >= k && !(grado(R) == 0 && R.front() == 0)){
		q = R[grado(R)];
		g = grado(R) - k;
		R[grado(R)] = 0;
		if(k != 0) R[g] -= q;
		quitar_ceros(R);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, k;
	while(true){
		cin >> n >> k;
		if(n == -1 && k == -1) break;
		vector<ull> R(n + 1);
		for(int i = 0; i < n + 1; i++){
			cin >> R[i];
		}
		quitar_ceros(R);
		dividir(R, k);
		for(int i = 0; i <= grado(R); i++){
			if(i > 0) cout << " ";
			cout << R[i];
		}
		cout << "\n";
	}
	return 0;
}