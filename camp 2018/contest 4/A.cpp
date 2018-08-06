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

const ll p = 7340033;
const ll root = 5;
const ll root_1 = 4404020;
const int root_pw = 1<<20;

ll inv(ll a, ll n){
    ll r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
    while(r1){
        si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
        ri = r0 % r1, r0 = r1, r1 = ri;
    }
    if(s0 < 0) s0 += n;
    return s0;
}

void swapPositions(vector<ll> & X){
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

void fft(vector<ll> & a, bool invert){
        int n = a.size();
        swapPositions(a);
        for (int len=2; len<=n; len<<=1) {
            ll wlen = invert ? root_1 : root;
            for (int i=len; i<root_pw; i<<=1)
                wlen = wlen * wlen % p;
            for (int i=0; i<n; i+=len) {
                ll w = 1;
                for (int j=0; j<len/2; ++j) {
                    int u = a[i+j],  v = a[i+j+len/2] * w % p;
                    a[i+j] = u+v < p ? u+v : u+v-p;
                    a[i+j+len/2] = u-v >= 0 ? u-v : u-v+p;
                    w = w * wlen % p;
                }
            }
        }
        if (invert) {
            ll nrev = inv (n, p);
            for (int i=0; i<n; ++i)
                a[i] = a[i] * nrev % p;
        }
}

int size;

void multiplyPolynomials(vector<ll> & P, vector<ll> & Q, bool same){
    int m = P.size();
    P.resize(size);
    fft(P, false);
    if(!same){
        Q.resize(size);
        fft(Q, false);
    }
	for(int i = 0; i < size; i++){
		if(same) P[i] = P[i] * P[i] % p;
        else P[i] = P[i] * Q[i] % p;
	}
	fft(P, true);
    P.resize(m);
}

ll nearest(ll m){
    int cont = -1;
    ll tmp = 1;
    ll m0 = m;
    while(m > 1){
        m >>= 1;
        tmp <<= 1;
        cont++;
    }
    if(tmp != m0) cont++;
    return max(0, cont);
}

void print(vector<ll> & arr){
    for(ll & x : arr){
        cout << x << " ";
    }
    cout << "\n\n";
}

int main()
{
    ios_base::sync_with_stdio();
    cin.tie(0);
    int n, m;
    cin >> m >> n;
    vector<ll> P(n + 1);
    for(int i = 0; i <= n; i++){
        cin >> P[i];
    }
    if(P[0] == 0){
        cout << "The ears of a dead donkey";
        return 0;
    }
    P.resize(m);
    //vector<ll> original = P;
    ll leading = inv(P[0], p);
    for(int i = 1; i < P.size(); i++){
        P[i] = - P[i] * leading % p;
        if(P[i] < 0) P[i] += p;
    }
    P[0] = 0;
    n = nearest(m);
    size = 2 * nearestPowerOfTwo(m);
    vector< vector<ll> > powers(n + 1);
    powers[0] = P;
    for(int k = 1; k <= n; k++){
        powers[k] = powers[k - 1];
        multiplyPolynomials(powers[k], powers[k], true);
    }
    for(int k = 0; k <= n; k++){
        powers[k][0] = 1;
    }
    for(int k = n; k >= 1; k--){
        multiplyPolynomials(powers[k - 1], powers[k], false);
    }
    for(int i = 0; i < m; i++){
        powers[0][i] = powers[0][i] * leading % p;
        if(powers[0][i] < 0) powers[0][i] += p;
        cout << powers[0][i] << " ";
    }
    //cout << "\n";
    //multiplyPolynomials(original, powers[0], false);
    //print(original);
    return 0;
}
