#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using comp = complex<ld>;
const ld PI = acosl(-1);

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

void fft(vector<comp> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<comp> wp(n>>1);
	for(int k = 1; k < n; k <<= 1){
		for(int j = 0; j < k; ++j)
			wp[j] = polar(1.0l, PI * j / k * inv);
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				comp t = X[i + j + k] * wp[j];
				X[i + j + k] = X[i + j] - t;
				X[i + j] += t;
			}
		}
	}
	if(inv == -1)
		for(int i = 0; i < n; ++i)
			X[i] /= n;
}

vector<ld> conv(const vector<ld> & A, const vector<ld> & B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	vector<comp> C(size);
	comp I(0, 1);
	for(int i = 0; i < A.size() || i < B.size(); ++i){
		if(i < A.size()) C[i] += A[i];
		if(i < B.size()) C[i] += I*B[i];
	}
	fft(C, 1);
	vector<comp> D(size);
	for(int i = 0, j = 0; i < size; ++i){
		j = (size-1) & (size-i);
		D[i] = (conj(C[j]*C[j]) - C[i]*C[i]) * 0.25l * I;
	}
	fft(D, -1);
	vector<ld> E;
	for_each(D.begin(), D.begin() + sz, [&](comp x){E.push_back(x.real());});
	return E;
}

vector<ld> inversePolynomial(const vector<ld> & A){
	vector<ld> R(1, 1.0l / A[0]);
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		vector<ld> R2 = R;
		vector<ld> a(min(c, A.size()));
		for(int i = 0; i < a.size(); ++i)
			a[i] = A[i];
		R2 = conv(R2, R2);
		R2.resize(c);
		R2 = conv(R2, a);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - R2[i];
		}
	}
	R.resize(A.size());
	return R;
}

vector<ld> derivative(vector<ld> A){
	for(int i = 0; i < A.size(); ++i)
		A[i] = A[i] * i;
	if(!A.empty()) A.erase(A.begin());
	return A;
}

vector<ld> integral(vector<ld> A){
	for(int i = 0; i < A.size(); ++i)
		A[i] = A[i] / (i+1);
	A.insert(A.begin(), 0);
	return A;
}

vector<ld> logarithm(vector<ld> A){
	int n = A.size();
	A = conv(derivative(A), inversePolynomial(A));
	A.resize(n);
	A = integral(A);
	A.resize(n);
	return A;
}

vector<ld> exponential(const vector<ld> & A){
	vector<ld> E(1, 1);
	while(E.size() < A.size()){
		size_t c = 2*E.size();
		E.resize(c);
		vector<ld> S = logarithm(E);
		for(int i = 0; i < c && i < A.size(); ++i){
			S[i] = A[i] - S[i];
		}
		S[0] = 1;
		E = conv(E, S);
		E.resize(c);
	}
	E.resize(A.size());
	return E;
}

auto divsSieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j].push_back(i);
		}
	}
	return divs;
}

auto muSieve(int n){
	vector<int> primes, mu(n+1), lp(n+1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
			else{
				mu[d] = -mu[i];
			}
		}
	}
	return mu;
}

const int N = 20;
const auto divs = divsSieve(21*N);
const auto mu = muSieve(21*N);

ld g(int n){
	ld ans = 0;
	for(int k = 1; k <= 21*n; ++k){
		ld term = 0;
		for(int d : divs[k]){
			if(mu[k/d] == 0) continue;
			vector<ld> P(n+1);
			for(int m : divs[d]){
				if(m > n) break;
				P[m] = 1.0l/m;
			}
			P = exponential(P);
			term += P[n] * mu[k/d];
		}
		//cout << k << " " << term << "\n";
		ans += k*k * term;
	}
	return ans;
}

void gen_partitions(int n, function<void(const vector<int>&)> f){
	vector<int> a(n);
	int k = 1, y = n-1;
	while(k != 0){
		int x = a[k-1] + 1;
		k--;
		while(2*x <= y){
			a[k] = x;
			y -= x;
			k++;
		}
		int l = k+1;
		while(x <= y){
			a[k] = x;
			a[l] = y;
			f(vector<int>(a.begin(), a.begin() + k+2));
			x++;
			y--;
		}
		a[k] = x+y;
		y = x+y-1;
		f(vector<int>(a.begin(), a.begin() + k+1));
	}
}

int main(){
	for(int k = 1; k <= 10; ++k){
		set<int> st;
		gen_partitions(k, [&](const vector<int>& f){
			int l = 1;
			for(int x : f) l = l / __gcd(l, x) * x;
			st.insert(l);
		});
		cout << k << " " << st.size() << "\n";
	}
	cout << g(N) << "\n";
	return 0;
}