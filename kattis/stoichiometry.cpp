#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b){
	int r;
	while(b != 0){
		r = a % b, a = b, b = r;
	}
	return a;
}

struct info{
	int pos, subindice;
};

struct frac{
	int num, den;

	frac(int nu, int de){
		num = nu, den = de;
		if(den < 0){
			num *= -1;
			den *= -1;
		}
		int d = gcd(abs(num), den);
		num /= d;
		den /= d;
	}

	frac(int nu){
		num = nu, den = 1;
	}

	frac sum(frac A){
		return frac(num * A.den + den * A.num, den * A.den);
	}

	frac subtract(frac A){
		return frac(num * A.den - den * A.num, den * A.den);
	}

	frac multiply(frac A){
		return frac(num * A.num, den * A.den);
	}

	frac divide(frac A){
		return frac(num * A.den, den * A.num);
	}

	bool isZero(){
		return num == 0;
	}
};

typedef vector<frac> tupla;
typedef vector<tupla> matriz;

void GJ(matriz & A, int m, int n){
	int i = 0, j = 0;
	while(i < m && j < n){
		if(A[i][j].isZero()){
			for(int k = i + 1; k < m; k++){
				if(!A[k][j].isZero()){
					swap(A[i], A[k]);
					break;
				}
			}
		}
		if(!A[i][j].isZero()){
			for(int l = n - 1; l >= j; l--){
				A[i][l] = A[i][l].divide(A[i][j]);
			}
			for(int k = 0; k < m; k++){
				if(i != k){
					for(int l = n - 1; l >= j; l--){
						A[k][l] = A[k][l].subtract(A[k][j].multiply(A[i][l]));
					}
				}
			}
			i++;
		}
		j++;
	}
}

bool zeroRow(tupla & A){
	for(frac & x : A){
		if(!x.isZero()) return false;
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0);
	int signo, n_m, m, n;
	int pos = 0;
	map<string, vector<info> > elementos;
	while(cin >> signo >> n_m && !(signo == 0 && n_m == 0)){
		map<string, int> counter;
		while(n_m--){
			string element;
			int count;
			cin >> element >> count;
			count *= signo;
			counter[element] += count;
		}
		for(auto & i : counter){
			elementos[i.first].push_back({pos, i.second});
		}
		pos++;
	}

	m = elementos.size(), n = pos;
	matriz A(m, tupla(n, 0));
	int i = 0;
	for(auto & elem : elementos){
		for(int j = 0; j < elem.second.size(); j++){
			A[i][elem.second[j].pos] = elem.second[j].subindice;
		}
		i++;
	}

	GJ(A, m, n);
	while(zeroRow(A.back())){
		A.pop_back();
		m--;
	}

	tupla ans(n, 0);

	for(int j = m; j < n; j++){
		int lcm = 1;
		for(int i = 0; i < m; i++){
			lcm *= A[i][j].den / gcd(A[i][j].den, lcm);
		}
		ans[j] = lcm;
	}

	for(int i = 0; i < m; i++){
		for(int j = m; j < n; j++){
			ans[i] = ans[i].subtract(A[i][j].multiply(ans[j]));
		}
	}

	int d = 0;
	for(frac & x : ans){
		d = gcd(d, x.num);
	}
	for(frac & x : ans){
		x.num /= d;
		cout << x.num << " ";
	}
	cout << "\n";
	return 0;
}