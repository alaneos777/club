#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef complex<ld> comp;
typedef long long int lli;
ld PI = acosl(-1.0L);

int reverseBits(int n, int size){
	int ans = 0;
	while(size--){
		ans = (ans << 1) | (n & 1);
		n >>= 1;
	}
	return ans;
}

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

int nBits(int n){
	int ans = 0;
	while(n){
		n >>= 1;
		ans++;
	}
	return ans;
}

int mod(int a, int b){
	int r = a % b;
	if(r < 0) r += b;
	return r;
}

void fft(vector<comp> & X, int inv){
	int n = X.size();
	int log2n = nBits(n) - 1;
	comp w1 = polar(1.0L, 2.0 * PI / n);
	vector<comp> w(n);
	comp r;
	w[0] = 1;
	for(int i = 1; i < n; i++){
		w[i] = w[i - 1] * w1;
	}
	for(int i = 0; i < n; i++){
		int pos = reverseBits(i, log2n);
		if(i < pos) swap(X[i], X[pos]);
	}
	int pot = n >> 1, len = 1;
	for(int i = 0; i < log2n; i++){
		for(int j = 0; j < len; j++){
			for(int k = 0; k < pot; k++){
				int first = j + 2 * len * k, second = first + len;
				r = w[mod(pot * j * inv, n)] * X[second];
				X[second] = X[first] - r;
				X[first] += r;
			}
		}
		pot >>= 1, len <<= 1;
	}
	if(inv == -1){
		for(int i = 0; i < n; i++){
			X[i] /= n;
		}
	}
}

lli m = 100003;

void multiplyPolynomials(vector<lli> & P, vector<lli> & Q, vector<lli> & ans){
	int degree = nearestPowerOfTwo(max(P.size(), Q.size())) << 1;
	vector<comp> A(P.size());
	vector<comp> B(Q.size());
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

void quitar(vector<lli> & X){
	int l = X.size();
	for(int i = l - 1; i >= 0; i--){
		if(X[i] == 0) X.pop_back();
		else break;
	}
	if(X.size() == 0) X.push_back(0);
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, q, k;
	lli ai;
	cin >> n;
	deque< vector<lli> > polinomios(n);
	for(int i = 0; i < n; i++){
		cin >> ai;
		polinomios[i] = {ai, 1};
	}
	while(polinomios.size() > 1){
		int len = polinomios.size() / 2;
		for(int i = 0; i < len; i += 2){
			vector<lli> tmp;
			multiplyPolynomials(polinomios[0], polinomios[1], tmp);
			polinomios.pop_front();
			polinomios.pop_front();
			polinomios.push_back(tmp);
		}
	}
	quitar(polinomios[0]);
	cin >> q;
	while(q--){
		cin >> k;
		cout << polinomios[0][polinomios[0].size() - k - 1] << "\n";
	}
	return 0;
}