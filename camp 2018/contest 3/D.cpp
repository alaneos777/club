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
    lli ai;
    lli num = 1, den = 1;
    lli sum = 0;
    for(int i = 1; i <= n; i++){
        cin >> ai;
        sum = (sum + ai + 1) % mod;
        num = num * i % mod;
        den = den * sum % mod;
    }
    lli ans = num * inv(den, mod) % mod;
    if(ans < 0) ans =+ mod;
    cout << ans;
    return 0;
}
