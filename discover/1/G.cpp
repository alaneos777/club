#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; ++i)
#define rep(i, a, b) for(int i = a; i < b; ++i)
#define eb emplace_back
#define pb push_back
#define fi first
#define se second
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

const int MX = 52;
const ll MOD = 1e9 + 7;

ll inv_mult[2 * MX + 2];
ll pascal[MX + 2][MX + 2];

ll eleva(ll a, ll e){
    ll ret = 1;
    while(e){
        if(e & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return ret;
}

ll T[MX + 2];
ll T_d[MX + 2];

ll dp[MX + 2][MX + 2];
bool calc[MX + 2][MX + 2];

ll f(int N, int B){
    if(B >= N) return 0;
    if(N == 1){
        return 1;
    }
    if(calc[N][B]) return dp[N][B];
    calc[N][B] = true;

    if(B == 0){
        dp[N][B] = T[N];
        for(int i = 1; i < N; i++){
            dp[N][B] = (dp[N][B] + MOD - f(N, i)) % MOD;
        }
        return dp[N][B];
    }

    ll res = 0;
    for(int n = 0; n <= N - 2; n++){
        ll aux = 0;
        for(int i = 0; i < B; i++){
            ll temp = (f(n + 1, i) * f(N - n - 1, B - i - 1)) % MOD;
            aux = (aux + temp) % MOD;
        }
        aux = (aux * pascal[N - 2][n]) % MOD;
        res = (res + aux) % MOD;
    }
    res = (res * N) % MOD;
    res = (res * (N - 1)) %  MOD;
    res = (res * inv_mult[2 * B]) % MOD;
    dp[N][B] = res;
    return res;
}

void init(){
    inv_mult[0] = 1;
    inv_mult[1] = 1;
    for(int i = 2; i <= 2 * MX; i++) inv_mult[i] = eleva(i, MOD - 2); 
    // pascal
    pascal[0][0] = 1;
    for(int i = 1; i <= MX; i++){
        pascal[i][0] = 1;
        for(int j = 1; j <= MX; j++){
            pascal[i][j] = (pascal[i - 1][j] + pascal[i - 1][j - 1]) % MOD;
        }
    }
    // cant de grafos conexos
    T[0] = 1;
    T_d[0] = 1;
    for(int n = 1; n <= MX; n++) T_d[n] = eleva(2, n * (n - 1) / 2);
    for(int n = 1; n <= MX; n++){
        T[n] = T_d[n];
        for(int k = 1; k < n; k++){
            ll aux = (pascal[n - 1][k - 1] * T[k]) % MOD;
            aux = (aux * T_d[n - k]) % MOD;
            T[n] = (T[n] + MOD - aux) % MOD;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    init();

    int N, B;
    cin >> N >> B;

    ll res = 0;
    forn(i, B + 1) res = (res + f(N, i)) % MOD;
    cout << res << endl;
    return 0;
}
