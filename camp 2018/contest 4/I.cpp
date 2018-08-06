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

void swapPositions(vector<vector<int>> & X, int row, bool transpose){
	int n = X.size();
	int j = n >> 1;
	for(int i = 1; i < n - 1; i++){
		if(i < j){
            if(transpose){
                swap(X[i][row], X[j][row]);
            }else{
                swap(X[row][i], X[row][j]);
            }
        }
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

void fft(vector<vector<int>> & a, int row, bool invert, bool transpose){
        int n = a.size();
        swapPositions(a, row, transpose);
        int len, wlen, i, j, w, u, v;
        for (len = 2; len <= n; len <<= 1) {
            int wlen = invert ? root_1 : root;
            for (i = len; i < root_pw; i <<= 1)
                wlen = int (wlen * 1ll * wlen % p);
            for (i = 0; i < n; i += len) {
                w = 1;
                for (int j = 0; j < len / 2; ++j) {
                    if(transpose){
                        u = a[i + j][row], v = int (a[i + j + len / 2][row] * 1ll * w % p);
                        a[i + j][row] = u + v < p ? u + v : u + v - p;
                        a[i + j + len/2][row] = u - v >= 0 ? u - v : u - v + p;
                    }else{
                        u = a[row][i + j], v = int (a[row][i + j + len / 2] * 1ll * w % p);
                        a[row][i + j] = u + v < p ? u + v : u + v - p;
                        a[row][i + j + len / 2] = u - v >= 0 ? u - v : u - v + p;
                    }
                    w = int (w * 1ll * wlen % p);
                }
            }
        }
        if (invert) {
            int nrev = inv (n, p);
            for (int i = 0; i < n; ++i){
                if(transpose)
                    a[i][row] = int (a[i][row] * 1ll * nrev % p);
                else
                    a[row][i] = int (a[row][i] * 1ll * nrev % p);
            }
        }
}

int n, sizeN;
int h, w;

void fft2D(vector<vector<int>> & P, bool invert){
    for(int i = 0; i < sizeN; i++){
        fft(P, i, invert, false);
    }
    for(int i = 0; i < sizeN; i++){
        fft(P, i, invert, true);
    }
}

void pointWise(vector<vector<int>> & P, vector<vector<int>> & Q){
    for(int i = 0; i < sizeN; i++){
        for(int j = 0; j < sizeN; j++){
            P[i][j] = P[i][j] * 1ll * Q[i][j] % p;  
        }
    }
}

int main()
{
    ios_base::sync_with_stdio();
    cin.tie(0);
    char c;
    cin >> h >> w;
    int n = max(h, w);
    int degree = 2 * (n - 1);
    int points = 0;
    sizeN = nearestPowerOfTwo(degree + 1);
    vector<vector<int>> P(sizeN, vector<int>(sizeN)), Q(sizeN, vector<int>(sizeN));
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            cin >> c;
            if(c == '1') points++;
            P[i][j] = Q[n - 1 - i][n - 1 - j] = c - '0';
        }
    }
    fft2D(P, false);
    fft2D(Q, false);
    pointWise(P, Q);
    fft2D(P, true);
    int x, y;
    double ans = 0;
    for(int i = 0; i <= degree; i++){
        for(int j = 0; j <= degree; j++){
            if(P[i][j] > 0){
                x = i - (n - 1);
                y = j - (n - 1);
                ans += P[i][j] * hypot(x, y);
            }
        }
    }
    ans = ans * 3 / points / (points - 1);
    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}
