#include <bits/stdc++.h>
using namespace std;
typedef complex<double> comp;
double PI = acos(-1.0);

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

void fft(vector<comp> & X, int inv){
	int n = X.size();
	int len, len2, i, j, k;
	for(i = 1, j = 0; i < n - 1; ++i){
		for(k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	double ang;
	comp t, u, v;
	vector<comp> wlen_pw(n >> 1);
	wlen_pw[0] = 1;
	for(len = 2; len <= n; len <<= 1){
		ang = inv == -1 ? -2 * PI / len : 2 * PI / len;
		len2 = len >> 1;
		comp wlen(cos(ang), sin(ang));
		for(i = 1; i < len2; ++i)
			wlen_pw[i] = wlen_pw[i - 1] * wlen;
		for(i = 0; i < n; i += len)
			for(j = 0; j < len2; ++j){
				t = X[i + j + len2] * wlen_pw[j];
				X[i + j + len2] = X[i + j] - t;
				X[i + j] += t;
			}
	}
	if(inv == -1)
		for(i = 0; i < n; ++i)
			X[i] /= n;
}

void square(vector<comp> & A){
	int degree = A.size() + A.size() - 2;
	int size = nearestPowerOfTwo(degree + 1);
	A.resize(size);
	fft(A, 1);
	for(int i = 0; i < size; i++){
		A[i] = A[i] * A[i];
	}
	fft(A, -1);
	A.resize(degree + 1);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, q, ai;
	cin >> n >> k >> q;
	vector<comp> P(200001);
	P[0] = 1;
	while(k--){
		cin >> ai;
		P[ai] += 1;
	}
	vector<int> Q(q);
	for(int & qi : Q)
		cin >> qi;
	int pot = *max_element(Q.begin(), Q.end());
	for(int i = 1; i < pot; i *= 2){
		square(P);
		P.resize(200001);
		for(int i = 0; i < P.size(); ++i){
			if((int)round(real(P[i])) > 0) P[i] = 1;
			else P[i] = 0;
		}
	}
	for(int i = 0; i < q; ++i){
		if((int)round(real(P[Q[i]])) == 0) cout << "No\n";
		else cout << "Yes\n";
	}
	return 0;
}