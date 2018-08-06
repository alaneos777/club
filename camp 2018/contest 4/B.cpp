#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef complex<double> comp;
typedef vector<comp> vc;
typedef vector<ll> vi;

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

void quitar(vector<comp> & X){
	while(X.size() && isZero(X.back())) X.pop_back();
	if(X.size() == 0) X.push_back(0);
}

void multiplyPolynomials(vector<comp> & A, vector<comp> & B){
	int degree = nearestPowerOfTwo(A.size() + B.size() - 1);
	A.resize(degree);
	B.resize(degree);
	fft(A, 1);
	fft(B, 1);
	for(int i = 0; i < degree; i++){
		A[i] *= B[i];
	}
	fft(A, -1);
	quitar(A);
}

string s;
char c;
vc a, b;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

	cin >> s;
	a = b = vc(s.size()+1);

	for (int i = 1; i < a.size(); i++)
        a[i] = b[i] = comp(int(s[i-1] == '1'), 0);

    multiplyPolynomials(a, b);

    ll res = 0;
    for (int i = 2; i < a.size(); i += 2) {
        if (i / 2 - 1 >= s.size())
            break;

        if (s[i/2-1] == '0')
            continue;

        res += ll(round(a[i].real()) - 1) / 2;
    }

    cout << res << endl;

	return 0;
}
