#include <bits/stdc++.h>
#define ld long double
#define endl '\n'
using namespace std;

typedef long long ll;
typedef complex<long double> comp;
typedef vector<comp> vc;
typedef vector<ll> vi;

long double PI = acos(-1.0L);

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

const int MAXN = 2000005;

comp wlen_pw[MAXN];

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

void fft(vector<comp> & a, int n, int invert){
        swapPositions(a);
        for(int len=2;len<=n;len <<= 1) {
            ld ang = 2 * PI / len * invert;
            int len2 = len >> 1;

            comp wlen(cos(ang), sin(ang));
            wlen_pw[0] = comp(1, 0);
            for(int i=1;i<len2;i++)
                    wlen_pw[i] = wlen_pw[i - 1] * wlen;

            comp t;
            int r,l;
            for(int i=0;i<n;i+=len) {
                for(int j=0;j<len/2;j++) {
                    r = i + j + len / 2; l = i + j;
                    t = a[r] * wlen_pw[j];
                    a[r] = a[l] - t;
                    a[l] += t;
                }
            }
        }

        if(invert == -1)
                for(int i=0;i<n;i++)
                    a[i] /= n;
}

void multiplyPolynomials(vector<comp> & A){
	int degree = nearestPowerOfTwo(2*A.size()-1);
	A.resize(degree);

	fft(A, A.size(), 1);

	for(int i = degree - 1; i >= 0; i--)
		A[i] *= A[i];

	fft(A, A.size(), -1);
}

int power (ll b, int p, int m) {
    ll res = 1;

    while (p) {
        if (p & 1) {
            res *= b;
            res %= m;
        }

        b *= b;
        b %= m;
        p >>= 1;
    }

    return res;
}

vc a, b;
vi acu, c, pot;
int n, m;;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

	cin >> n >> m;
    acu = c = pot = vi(m);

    for (int i = 1; i < m; i++) {
        pot[i] = power(i, n, m);
        acu[ pot[i] ]++;
    }

    a = vc(m);
    for (int i = 0; i < m; i++)
        a[i] = acu[i];
    multiplyPolynomials(a);

    ll res = 0;
    for (int i = 0; i < a.size(); i++) {
        c[i%m] += ll(a[i].real()+0.5);
    }

    for (int i = 1; i < m; i++) {
        c[(2*pot[i])%m]--;
        res += acu[(2*pot[i])%m];
    }

    for (int i = 0; i < m; i++) {
        assert(c[i] % 2 == 0);
        res += (c[i] / 2) * acu[i];
    }

    cout << res << endl;

	return 0;
}
