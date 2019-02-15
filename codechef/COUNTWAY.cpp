#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using comp = complex<ld>;
using lli = long long int;
const ld PI = acos(-1.0l);

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
	for(int k = 1; k < n; k <<= 1){
		comp wk = polar(1.0l, PI / k * inv);
		for(int i = 0; i < n; i += k << 1){
			comp w(1);
			for(int j = 0; j < k; ++j, w = w * wk){
				comp t = X[i + j + k] * w;
				X[i + j + k] = X[i + j] - t;
				X[i + j] += t;
			}
		}
	}
	if(inv == -1)
		for(int i = 0; i < n; ++i)
			X[i] /= n;
}

const int mod = 13313;

vector<int> conv(const vector<int> & A, const vector<int> & B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	vector<comp> C(size);
	comp I(0, 1);
	for(int i = 0; i < A.size() || i < B.size(); ++i){
		if(i < A.size()) C[i] += A[i];
		if(i < B.size()) C[i] += comp(0, B[i]);
	}
	fft(C, 1);
	vector<comp> D(size);
	for(int i = 0, j = 0; i < size; ++i){
		j = (size-1) & (size-i);
		D[i] = (conj(C[j]*C[j]) - C[i]*C[i]) * 0.25l * I;
	}
	fft(D, -1);
	vector<int> ans(sz);
	for(int i = 0; i < sz; ++i){
		ans[i] = ((lli)round(D[i].real())) % mod;
	}
	return ans;
}

auto custom = [](const vector<int> & a, const vector<int> & b){
	return a.size() > b.size();
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, ai;
	cin >> n >> k;
	vector<int> freq(200001);
	for(int i = 0; i < n; ++i){
		cin >> ai;
		freq[ai]++;
	}
	priority_queue<vector<int>, vector<vector<int>>, decltype(custom)> Q(custom);
	for(int i = 0; i < freq.size(); ++i){
		if(freq[i]){
			Q.push(vector<int>(freq[i] + 1, 1));
		}
	}
	while(Q.size() > 1){
		vector<int> a = Q.top(); Q.pop();
		vector<int> b = Q.top(); Q.pop();
		Q.push(conv(a, b));
	}
	cout << Q.top()[k] << "\n";
	return 0;
}