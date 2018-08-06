#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli gcd(lli a, lli b){
	lli r;
	while(b != 0){
		r = a % b, a = b, b = r;
	}
	return a;
}

struct frac{
	lli num, den;
	frac(){
		num = 0, den = 1;
	}
	frac(lli a, lli b){
		if(b < 0){
			a *= -1;
			b *= -1;
		}
		lli d = gcd(abs(a), b);
		num = a / d;
		den = b / d;
	}
	bool isZero(){
		return num == 0;
	}
	bool isOne(){
		return num == 1 && den == 1;
	}
};

ostream &operator<<(ostream &os, const frac & f) {
	stringstream ss;
    ss << f.num;
    if(f.den != 1) ss << "/" << f.den;
    return os << ss.str();
}

istream &operator>>(istream &is, frac & f){
    lli num = 0, den = 1;
    string str;
    is >> str;
    size_t pos = str.find("/");
    if(pos == string::npos){
        istringstream(str) >> num;
    }else{
        istringstream(str.substr(0, pos)) >> num;
        istringstream(str.substr(pos + 1)) >> den;
    }
    frac nueva(num, den);
    f = nueva;
    return is;
}

frac sum(frac a, frac b){
	lli d = gcd(a.den, b.den);
	return frac(a.num * (b.den / d) + b.num * (a.den / d), a.den * (b.den / d));
}

frac mult(frac a, frac b){
	lli d1 = gcd(abs(a.num), b.den);
	lli d2 = gcd(abs(b.num), a.den);
	return frac((a.num / d1) * (b.num / d2), (a.den / d2) * (b.den / d1));
}

typedef vector<frac> tupla;
typedef vector<tupla> matriz;

struct sistema{
	matriz A;
	tupla b;
};

void tipo1(sistema & S, int k, frac c){
	for(int j = 0; j < S.A[k].size(); j++){
		if(!S.A[k][j].isZero() && !c.isZero()) S.A[k][j] = mult(S.A[k][j], c);
	}
	if(!S.b[k].isZero() && !c.isZero()) S.b[k] = mult(S.b[k], c);
}

void tipo2(sistema & S, int i, int k){
	swap(S.A[i], S.A[k]);
	swap(S.b[i], S.b[k]);
}

void tipo3(sistema & S, int k, int l, frac c){
	for(int j = 0; j < S.A[k].size(); j++){
		if(!S.A[l][j].isZero() && !c.isZero()) S.A[k][j] = sum(S.A[k][j], mult(c, S.A[l][j]));
	}
	if(!S.b[l].isZero() && !c.isZero()) S.b[k] = sum(S.b[k], mult(c, S.b[l]));
}

void GaussJordan(sistema & S){
	int m = S.A.size();
	int n = S.A[0].size();
	int i = 0, j = 0;
	frac inv;
	while(i < m && j < n){
		if(S.A[i][j].isZero()){
			for(int k = i + 1; k < m; k++){
				if(!S.A[k][j].isZero()){
					tipo2(S, i, k);
					break;
				}
			}
		}
		if(!S.A[i][j].isZero()){
			inv = frac(S.A[i][j].den, S.A[i][j].num);
			tipo1(S, i, inv);
			for(int k = 0; k < m; k++){
				if(k != i){
					inv = frac(-S.A[k][j].num, S.A[k][j].den);
					tipo3(S, k, i, inv);
				}
			}
			i++;
		}
		j++;
	}
}

bool consistente(sistema & S){
	int m = S.A.size();
	int n = S.A[0].size();
	for(int i = 0; i < m; i++){
		int pos = -1;
		for(int j = i; j < n; j++){
			if(S.A[i][j].isOne()){
				pos = j;
				break;
			}
		}
		if(pos == -1){
			if(!S.b[i].isZero()) return false;
		}
	}
	return true;
}

int parametros(sistema & S){
	int m = S.A.size();
	int n = S.A[0].size();
	int params = 0, pos = 0;
	for(int i = 0; i < m; i++){
		while(pos < n && !S.A[i][pos].isOne()){
			params++, pos++;
		}
		pos++;
	}
	while(pos < n){
		params++, pos++;
	}
	return params;
}

int main(){
	ios_base::sync_with_stdio(0);
	int caso;
	while(cin >> caso && caso != 0){
		if(caso > 1) cout << "\n";
		int n, m;
		cin >> n >> m;
		sistema S;
		S.A = matriz(m, tupla(n));
		S.b = tupla(m);
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				cin >> S.A[i][j];
			}
			cin >> S.b[i];
		}
		GaussJordan(S);
		cout << "Solution for Matrix System # " << caso << "\n";
		if(consistente(S)){
			int params = parametros(S);
			if(params == 0){
				for(int j = 0; j < n; j++){
					cout << "x[" << (j + 1) << "] = " << S.b[j] << "\n";
				}
			}else{
				cout << "Infinitely many solutions containing " << params << " arbitrary constants.\n";
			}
		}else{
			cout << "No Solution.\n";
		}
	}
	return 0;
}