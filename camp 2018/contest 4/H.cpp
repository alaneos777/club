#include <bits/stdc++.h>
#define ld long double
#define endl '\n'
using namespace std;

typedef long long int ll;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

const int p = 7340033;
const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1<<20;

int inv(int a, int n){
    int r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
    while(r1){
        si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
        ri = r0 % r1, r0 = r1, r1 = ri;
    }
    if(s0 < 0) s0 += n;
    return s0;
}

ll modPow(ll a, ll b, ll mod){
    ll ans = 1;
    a %= mod;
    if(a < 0) a += mod;
    if(b < 0){
        a = inv(a, mod);
        b *= -1;
    }
    while(b){
        if(b & 1) ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}

void swapPositions(vector<int> & X){
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

void fft(vector<int> & a, bool invert){
        int n = a.size();
        swapPositions(a);
        for (int len=2; len<=n; len<<=1) {
            int wlen = invert ? root_1 : root;
            for (int i=len; i<root_pw; i<<=1)
                wlen = int (wlen * 1ll * wlen % p);
            for (int i=0; i<n; i+=len) {
                int w = 1;
                for (int j=0; j<len/2; ++j) {
                    int u = a[i+j],  v = int (a[i+j+len/2] * 1ll * w % p);
                    a[i+j] = u+v < p ? u+v : u+v-p;
                    a[i+j+len/2] = u-v >= 0 ? u-v : u-v+p;
                    w = int (w * 1ll * wlen % p);
                }
            }
        }
        if (invert) {
            int nrev = inv (n, p);
            for (int i=0; i<n; ++i)
                a[i] = int (a[i] * 1ll * nrev % p);
        }
}

int size, m = 100001;

void multiplyPolynomials(vector<int> & P, vector<int> & Q, bool same){
    fft(P, false);
    if(!same){
        fft(Q, false);
    }
	for(int i = 0; i < size; i++){
		if(same) P[i] = P[i] * 1ll * P[i] % p;
        else P[i] = P[i] * 1ll * Q[i] % p;
	}
	fft(P, true);
    for(int i = m; i < size; i++){
        P[i] = 0;
    }
}

int nearest(int m){
    int cont = -1;
    int tmp = 1;
    int m0 = m;
    while(m > 1){
        m >>= 1;
        tmp <<= 1;
        cont++;
    }
    if(tmp != m0) cont++;
    return max(0, cont);
}

void print(vector<int> & arr){
    for(int & x : arr){
        cout << x << " ";
    }
    cout << "\n\n";
}

vector<int> factorial, factorialInv;

int main()
{
    ios_base::sync_with_stdio();
    cin.tie(0);
    int n;
    cin >> n;

    factorial.resize(m + 1), factorialInv.resize(m + 1);
    factorial[0] = factorialInv[0] = 1;
    for(ll i = 1; i < factorial.size(); i++){
        factorial[i] = factorial[i - 1] * i % p;
        factorialInv[i] = inv(factorial[i], p) % p;
    }

    vector<int> P(m);
    for(ll i = 1; i < m; i++){
        P[i] = p -  modPow(2, i * (i - 1) / 2, p) * 1ll * factorialInv[i] % p;
    }
    int M = nearest(m);
    size = nearestPowerOfTwo(2 * m - 1);
    vector< vector<int> > powers(M + 1);
    P.resize(size);
    powers[0] = P;
    for(int k = 1; k <= M; k++){
        powers[k] = powers[k - 1];
        multiplyPolynomials(powers[k], powers[k], true);
    }
    for(int k = 0; k <= M; k++){
        powers[k][0] += 1;
    }
    for(int k = M; k >= 1; k--){
        multiplyPolynomials(powers[k - 1], powers[k], false);
    }
    for(int i = 1; i <= n; i++){
        powers[0][i] = -powers[0][i] * 1ll * factorial[i] % p;
        if(powers[0][i] < 0) powers[0][i] += p;
        cout << powers[0][i] << "\n";
    }
    return 0;
}
