#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli powmod(lli a, lli b, lli m){
    lli ans = 1;
    a %= m;
    while(b){
        if(b & 1) ans = (ans * a) % m;
        b >>= 1;
        a = (a * a) % m;
    }
    return ans;
}

lli inv(lli a, lli m){
    return powmod(a, m - 2, m);
}

lli mod = 1e9 + 7;

int main()
{
    ios_base::sync_with_stdio();
    cin.tie(0);
    int n;
    cin >> n;
    vector<lli> coef(n);
    coef[0] = 1;
    for(int i = 1; i < n; i++){
        for(int j = i; j >= 1; j--){
            coef[j] = (coef[j] + i * coef[j - 1] % mod) % mod;
        }
    }
    int alt = 1;
    lli ans = 0;
    lli pot = 2;
    for(int i = 1; i < n; i++){
        ans = (ans + alt * coef[i] * inv(pot - 1, mod) % mod) % mod;
        pot = pot * 2 % mod;
        alt *= -1;
    }
    if(ans < 0) ans += mod;
    cout << ans;
    return 0;
}
