#include <bits/stdc++.h>
using namespace std;
using comp = complex<double>;
using Vec = vector<comp>;
using lli = long long int;
const double pi = acos(-1);

void fft_slow(Vec & x, int inv){
	int n = x.size();
	Vec res(n);
	for(int j = 0; j < n; ++j){
		comp w = polar(1.0, 2*pi*inv*j/n), wk = 1;
		for(int k = 0; k < n; ++k, wk *= w)
			res[j] += x[k] * wk;
	}
	if(inv == -1)
		for(int k = 0; k < n; ++k)
			res[k] /= n;
	x = res;
}

void fft_rec(Vec & x, int inv){
	int n = x.size();
	if(n == 1) return;
	Vec even(n/2), odd(n/2);
	for(int k = 0; k < n; ++k){
		if(k&1) odd[k/2] = x[k];
		else even[k/2] = x[k];
	}
	fft_rec(even, inv), fft_rec(odd, inv);
	comp w = polar(1.0, 2*pi*inv/n), wk = 1, u, v;
	for(int k = 0; k < n/2; ++k, wk *= w){
		u = even[k], v = wk * odd[k];
		x[k] = u + v;
		x[k+n/2] = u - v;
	}
	if(inv == -1)
		for(int k = 0; k < n; ++k)
			x[k] /= 2;
}

/*int log2(int n){
	int l = 0;
	while(n >>= 1) l++;
	return l;
}

void fft_iter(Vec & x, int inv){
	int n = x.size();
	int nivs = log2(n);
	Vec tmp(n);
	for(int d = 0; d < nivs; ++d){
		cout << "Nivel " << d << ":\n";
		int blocks = 1 << d;
		int sz = n >> (d + 1);
		comp w = polar(1.0, 2.0 * pi * inv / (1 << (d + 1)));
		for(int k = 0; k < blocks; ++k){
			cout << " k = " << k << ":\n";
			for(int j = 0; j < sz; ++j){
				tmp[j+k*sz] = x[j+2*k*sz] + pow(w, k) * x[j+(2*k+1)*sz];
				tmp[j+k*sz+n/2] = x[j+2*k*sz] - pow(w, k) * x[j+(2*k+1)*sz];
				cout << "  (" << j+k*sz << ", " << j+k*sz+n/2 << ") <-- (" << j+2*k*sz << "," << j+(2*k+1)*sz << ")\n";
			}
		}
		x = tmp;
	}
	if(inv == -1)
		for(int k = 0; k < n; ++k)
			x[k] /= n;
}*/

void fft_iter(Vec & x, int inv){
	int n = x.size(), h = n>>1, sz = h, d, r, j, k;
	Vec tmp(n);
	for(d = 0; (r = 1<<d) < n; ++d, sz >>= 1){
		comp w = polar(1.0, pi*inv/r), wk = 1, u, v;
		for(k = 0; k < h; k += sz, wk *= w){
			for(j = k; j < k+sz; ++j){
				u = x[j+k], v = wk * x[j+k+sz];
				tmp[j] = u + v;
				tmp[j+h] = u - v;
			}
		}
		x = tmp;
	}
	if(inv == -1)
		for(k = 0; k < n; ++k)
			x[k] /= n;
}

int nearest(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

void linear_convolution(Vec & a, Vec & b){
	int m = a.size(), n = b.size();
	int sz = m + n - 1;
	int N = nearest(sz);
	a.resize(N), b.resize(N);
	fft_iter(a, 1), fft_iter(b, 1);
	for(int k = 0; k < N; ++k)
		a[k] *= b[k];
	fft_iter(a, -1);
	a.resize(sz);
}

void bluestein(Vec & x, int inv){
	int n = x.size();
	comp w = polar(1.0, pi * inv / n), w1 = w, w2 = 1;
	Vec p(n), q(2*n-1), b(n);
	for(int k = 0; k < n; ++k, w2 *= w1, w1 *= w*w){
		b[k] = w2;
		p[k] = x[k] * b[k];
		q[n-1-k] = q[n-1+k] = (comp)1 / b[k];
	}
	linear_convolution(p, q);
	for(int k = 0; k < n; ++k){
		if(inv == -1) x[k] = b[k] * p[n-1+k] / (comp)n;
		else x[k] = b[k] * p[n-1+k];
	}
}

void test_fft(){
	int degX, degY;
	cin >> degX >> degY;
	vector<comp> X(degX + 1), Y(degY + 1);
	for(int i = 0; i <= degX; i++) cin >> X[i];
	for(int i = 0; i <= degY; i++) cin >> Y[i];
	std::clock_t start;
	double duration;
	start = std::clock();
	linear_convolution(X, Y);
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	for(int i = 0; i < X.size(); i++) cout << X[i].real() << " ";
	cout << "\n" << duration << "\n";
}

void test_random_fft(){
	int deg = 1e6;
	vector<comp> A(deg + 1), B(deg + 1);
	for(int i = 0; i <= deg; i++){
		A[i] = rand() % 10;
		B[i] = rand() % 10;
	}
	clock_t start = clock();
	linear_convolution(A, B);
	double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	cout << duration << "\n";
}

int main(){
	srand(time(0));
	test_fft();
	return 0;
}