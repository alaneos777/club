#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

const lli p = 7340033;
const lli root = 5;
const lli root_1 = 4404020;
const int root_pw = 1<<20;

lli inv(lli a, lli n){
    lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
    while(r1){
        si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
        ri = r0 % r1, r0 = r1, r1 = ri;
    }
    if(s0 < 0) s0 += n;
    return s0;
}

lli modPow(lli a, lli b, lli mod){
    lli ans = 1;
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

void swapPositions(vector<lli> & X){
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

void fft(vector<lli> & a, bool invert){
        int n = a.size();
        swapPositions(a);
        for (int len=2; len<=n; len<<=1) {
            lli wlen = invert ? root_1 : root;
            for (int i=len; i<root_pw; i<<=1)
                wlen = wlen * wlen % p;
            for (int i=0; i<n; i+=len) {
                lli w = 1;
                for (int j=0; j<len/2; ++j) {
                    int u = a[i+j],  v = a[i+j+len/2] * w % p;
                    a[i+j] = u+v;
                    a[i+j+len/2] = u-v;
                    if(a[i+j] >= p) a[i+j]-=p;
                    if(a[i+j+len/2] < 0) a[i+j+len/2]+=p;
                    w = w * wlen % p;
                }
            }
        }
        if (invert) {
            lli nrev = inv (n, p);
            for (int i=0; i<n; ++i)
                a[i] = a[i] * nrev % p;
        }
}

vector<lli> multiplyPolynomials(vector<lli> & A, vector<lli> & B){
    int degA = A.size() - 1, degB = B.size() - 1, degC = degA + degB;
    int size = nearestPowerOfTwo(degC + 1);
    A.resize(size);
    B.resize(size);
    fft(A, false);
    fft(B, false);
    vector<lli> C(size);
    for(int i = 0; i < size; i++){
        C[i] = A[i] * B[i] % p;
    }
    fft(C, true);
    C.resize(degC + 1);
    return C;
}

vector<lli> factorial, factorialInv;

lli ncr(lli n, lli r){
    if(r < 0 || r > n) return 0;
    return factorial[n] * factorialInv[r] % p * factorialInv[n - r] % p;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int a, b, c, n;
    cin >> n >> a >> b >> c;
    lli m = a + b + c;
    factorial.resize(m + 1), factorialInv.resize(m + 1);
    factorial[0] = factorialInv[0] = 1;
    for(int i = 1; i < factorial.size(); i++){
        factorial[i] = factorial[i - 1] * i % p;
        factorialInv[i] = inv(factorial[i], p) % p;
    }

    vector<lli> A(a + 1), B(b + 1);
    for(int i = 0; i <= a; i++){
        A[i] = ncr(a, i);
        if(i & 1) A[i] = p - A[i];
    }
    for(int i = 0; i <= b; i++){
        B[i] = ncr(b, i);
    }
    vector<lli> C = multiplyPolynomials(A, B);
    lli ans = 0;
    for(int i = 0; i < C.size(); i++){
        ans = (ans + C[i] * modPow(m - 2 * i, n, p) % p) % p;
    }
    ans = ans * modPow(2, -a - b, p) % p;
    cout << ans;
    return 0;
}