#include <bits/stdc++.h>
using namespace std;
typedef complex<double> comp;
typedef long long int lli;
double PI = acosl(-1.0);

vector<lli> primos;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

bool isZero(comp z){
	return abs(z.real()) < 1e-3;
}

void swapPositions(vector<comp> & X){
	int n = X.size();
	int j = n >> 1;
	for(int i = 1; i < n - 1; i++){
		if(i < j) swap(X[i], X[j]);
		int k = n >> 1;
		while(j >= k){
			j -= k;
			k >>= 1;
		}
		if(j < k){
			j += k;
		}
	}
}

void criba(lli n){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

lli exp_bin_mod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % m;
		b >>= 1;
		a = (a * a) % m;
	}
	return ans;
}

lli primitiveRoot(lli n){
	lli phi_n = n - 1;
	vector<lli> factores;
	for(lli & p : primos){
		if(p * p > phi_n) break;
		if(phi_n % p == 0){
			while(phi_n % p == 0){
				phi_n /= p;
			}
			factores.push_back(p);
		}
	}
	if(phi_n > 1) factores.push_back(phi_n);
	for(lli i = 1; i < n; i++){
		bool test = true;
		for(lli & f : factores){
			if(exp_bin_mod(i, (n - 1) / f, n) == 1){
				test = false;
				break;
			}
		}
		if(test){
			return i;
		}
	}
}

void fft(vector<lli> & X, int inv){
	int n = X.size();
	swapPositions(X);
	comp w1 = polar(1.0, 2.0 * PI * inv / n);
	vector<comp> w(n);
	w[0] = 1;
	for(int i = 1; i < n; i++){
		w[i] = w[i - 1] * w1;
	}
	int pot = n >> 1;
	for(int i = 1; i < n; i <<= 1){
		for(int j = 0; j < i; j++){
			for(int k = 0; k < pot; k++){
				int first = j + 2 * i * k, second = first + i;
				comp r = w[pot * j] * X[second];
				X[second] = X[first] - r;
				X[first] += r;
			}
		}
		pot >>= 1;
	}
	if(inv == -1){
		for(int i = 0; i < n; i++){
			X[i] /= n;
		}
	}
}

void quitar(vector<lli> & X){
	while(X.back() == 0) X.pop_back();
	if(X.size() == 0) X.push_back(0);
}

void multiplyPolynomials(vector<lli> & P, vector<lli> & Q, vector<lli> & ans, lli m){
	int degree = nearestPowerOfTwo(P.size() + Q.size() - 1);
	vector<comp> A(P.size()), B(Q.size());
	for(int i = 0; i < A.size(); i++){
		A[i] = P[i];
	}
	for(int i = 0; i < B.size(); i++){
		B[i] = Q[i];
	}
	A.resize(degree);
	B.resize(degree);
	fft(A, 1);
	fft(B, 1);
	for(int i = 0; i < degree; i++){
		A[i] *= B[i];
	}
	fft(A, -1);
	ans.resize(A.size());
	for(int i = 0; i < ans.size(); i++){
		ans[i] = ((lli)round(A[i].real())) % m;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(316228);
	int t;
	cin >> t;
	while(t--){
		lli n, p;
		cin >> n >> p;
		if(n >= p){
			cout << "0\n";
			continue;
		}
		lli m = sqrt(n);
		deque< vector<lli> > polinomios(m);
		for(lli i = 0; i < m; i++){
			polinomios[i] = {i + 1, 1};
		}
		while(polinomios.size() > 1){
			int len = polinomios.size() / 2;
			for(int i = 0; i < len; i += 2){
				vector<lli> tmp;
				multiplyPolynomials(polinomios[0], polinomios[1], tmp, p);
				polinomios.pop_front();
				polinomios.pop_front();
				polinomios.push_back(tmp);
			}
		}
		quitar(polinomios[0]);
		for(int i = 0; i < polinomios[0].size(); i++){
			cout << polinomios[0][i] << "\n";
		}
		/*lli ans = 1;
		for(lli i = 0; i < m; i++){
			lli tmp = 0;
			for(lli j = polinomios[0].size() - 1; j >= 0; j--){
				tmp = (((tmp * i) % p) * m) % p;
				tmp = (tmp + polinomios[0][j]) % p;
			}
			ans = (ans * tmp) % p;
		}
		for(lli i = m * m + 1; i <= n; i++){
			ans = (ans * i) % p;
		}
		cout << ans << "\n";*/
	}
	return 0;
}