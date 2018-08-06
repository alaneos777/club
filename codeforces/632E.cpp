#include <bits/stdc++.h>
using namespace std;
typedef complex<double> comp;
double PI = acos(-1.0);

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

void fft(vector<comp> & X, int inv){
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

void quitar(vector<bool> & X){
	while(!X.back()) X.pop_back();
	if(X.size() == 0) X.push_back(0);
}

vector<bool> multiplyPolynomials(vector<bool> & P, vector<bool> & Q){
	int size = nearestPowerOfTwo(P.size() + Q.size() - 1);
	vector<comp> A(size), B(size);
	for(int i = 0; i < P.size(); i++){
		A[i] = P[i];
	}
	for(int i = 0; i < Q.size(); i++){
		B[i] = Q[i];
	}
	fft(A, 1);
	fft(B, 1);
	for(int i = 0; i < size; i++){
		A[i] *= B[i];
	}
	fft(A, -1);
	vector<bool> ans(size);
	for(int i = 0; i < size; i++){
		ans[i] = !isZero(A[i]);
	}
	quitar(ans);
	return ans;
}

vector<bool> exp_bin_pol(vector<bool> & P, int n){
	vector<bool> ans = {1};
	while(n){
		if(n & 1) ans = multiplyPolynomials(ans, P);
		n >>= 1;
		P = multiplyPolynomials(P, P);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, k, ai;
	cin >> n >> k;
	vector<bool> P(1001);
	for(int i = 0; i < n; i++){
		cin >> ai;
		P[ai] = 1;
	}
	P = exp_bin_pol(P, k);
	for(int i = 0; i < P.size(); i++){
		if(P[i]) cout << i << " ";
	}
	return 0;
}