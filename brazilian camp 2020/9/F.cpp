#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

const int MX = 1e5;
const ld eps = 1e-9;

const int n = 360000;
const ll mod = 1e8 + 7;

ll power(ll a, ll b){
    ll ans = 1;
    while(b){
        if(b & 1) ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}

const ll inv = power(n, mod-2);

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    vector<int> divs;
    for(int i = 1; i <= n; ++i){
        if(n % i == 0) divs.pb(i);
    }
    vector<int> phi(n+1);
    iota(all(phi), 0);
    for(int i = 2; i <= n; ++i){
        if(phi[i] == i){
            for(int j = i; j <= n; j += i){
                phi[j] -= phi[j] / i;
            }
        }
    }
    int s, p;
    while(cin >> s >> p && !(s == -1 && p == -1)){
        vector<bool> valid(n);
        forn(i, p){
            int a;
            cin >> a;
            valid[a] = 1;
        }
        ll ans = 0;
        ll den = 0;
        for(int d : divs){
            int len = n/d;
            int pot = 0;
            bool test = true;
            forn(start, d){
                int validos = 0;
                for(int k = 0; k < len; ++k){
                    validos += valid[(start + k*d) % n];
                }
                if(validos == len){
                    pot++;
                }else if(validos == 0){
                    //
                }else{
                    test = false;
                }
            }
            if(test){
                den+=phi[len];
                ans += (ll)phi[len] * power(s, pot) % mod;
                if(ans >= mod) ans -= mod;
            }
        }
        ans = ans * power(den, mod-2) % mod;
        cout << ans << "\n";
    }
    return 0;
}

