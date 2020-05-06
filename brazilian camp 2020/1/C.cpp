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
 
const int MX = 1e5, mod = 1000000009;
int n, k, mem[301][301][299][2];
 
int dp (int n, int i, int k, int f) {
    if (n == 3) return k == 1 && f;
    if (k < 0) return 0;
    if (i == n) return k == 0 && f;
    if (i < 2) {
        if (f) return dp(n, i+1, k, 1);
        return 0;
    }
    
    int &res = mem[n][i][k][f];
    if (res != -1) return res;
    res = 0;
    
    if (f) {
        res += dp(n, i+1, k, 1);
        if (res >= mod) res -= mod;
        
        res += dp(n-1, i-1, k-1, 1);
        if (res >= mod) res -= mod;
        
        res += dp(n-1, i-1, k, 0);
        if (res >= mod) res -= mod;
    } else {
        res += dp(n-1, i-1, k, 1);
        if (res >= mod) res -= mod;
        
        res += dp(n-1, i-1, k, 0);
        if (res >= mod) res -= mod;
    }
    
    return res;
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    memset(mem, -1, sizeof(mem));
    
    cin >> n >> k;
    cout << dp(n, 2, k, 1) << endl;
    
    return 0;
}