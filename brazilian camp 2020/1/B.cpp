#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
using namespace std;
 
using pii = pair<int, int>;
using vi = vector<int>;
using ll = long long;
using ld = long double;
 
const int MX = 300;
 
const ll MOD = 1e9 + 9;
 
int k;
 
ll dp[MX + 2][MX + 2];
int calc[MX + 2][MX + 2];
int nivel;
 
ll f(int n, int A){
    if(n == 1){
        if(A > 1) return 0;
        return 1;
    }
 
    if(calc[n][A] == nivel) return dp[n][A];
    calc[n][A] = nivel;
 
    ll ret = f(n - 1, A);
 
    if(A > 0) ret = (ret + f(n - 1, A - 1)) % MOD;
    if(A < k) ret = (ret + f(n - 1, A + 1)) % MOD;
    dp[n][A] = ret;
    return ret;
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int n;
    cin >> n >> k;
 
    if(k == 0){
        cout << 1 << endl;
        return 0;
    }
 
    nivel++;
    ll resp = f(n, 0);
 
    k--;
    nivel++;
    resp = (resp + MOD - f(n, 0)) % MOD;
    cout << resp << endl;
 
    return 0;
}
