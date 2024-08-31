#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

lli power(lli a, lli b){
    lli ans = 1;
    while(b){
        if(b&1) ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}

using poly = vector<int>;

poly operator/(const poly& a, const poly& b){
    int n = a.size();
    poly c(n);
    c[0] = a[0];
    for(int i = 1; i < n; ++i){
        c[i] = a[i];
        for(int j = 1; j <= i && j < b.size(); ++j){
            c[i] -= (lli)b[j] * c[i-j] % mod;
            if(c[i] < 0) c[i] += mod;
        }
    }
    return c;
}

const int M = 1e7 + 10;
vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);

lli ncr(int n, int r){
    if(r < 0 || r > n) return 0;
    return (lli)fact[n] * invfact[r] % mod * invfact[n-r] % mod;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for(lli i = 2; i <= M; ++i){
        fact[i] = fact[i-1] * i % mod;
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
        invfact[i] = (lli)invfact[i-1] * inv[i] % mod;
    }
    lli r; int d;
    cin >> r >> d;
    lli q = r * power(((1-r)%mod+mod)%mod, mod-2) % mod;
    lli q_dp1 = power(q, d+1);
    poly num(d+2);
    num[0] = 1;
    lli alt = (d+1) % 2 == 0 ? 1 : mod-1;
    for(int i = 0; i <= d+1; ++i){
        num[i] -= q_dp1 * ncr(d+1, i) % mod * alt % mod;
        if(num[i] < 0) num[i] += mod;
        alt = mod-alt;
    }
    poly den = {1, ((mod-r)%mod+mod)%mod};
    poly P = num / den;
    lli ans = 0;
    for(int i = 0; i <= d; ++i){
        ans += P[i] * power(i, d) % mod;
        if(ans >= mod) ans -= mod;
    }
    cout << ans << "\n";
    return 0;
}