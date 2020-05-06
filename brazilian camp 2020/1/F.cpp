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
 
const int MX = 1e5;
const int MAXPRIMOS = 21;
 
const ld eps = 1e-9;
 
const ll MOD = 1e9 + 9;
 
ld le(ld a, ld b) { return b - a > eps; }
 
int primos[MAXPRIMOS + 2];
int cnt_primos;
ld logaritmo[MAXPRIMOS + 2];
 
vi divisores[MX + 2];
 
ld dp[MAXPRIMOS + 2][MX + 2];
bool calc[MAXPRIMOS + 2][MX + 2];
int sol[MAXPRIMOS + 2][MX + 2];
 
void init(){
    for(int d = 2; d <= MX; d++){
        if(divisores[d].empty() && cnt_primos <= MAXPRIMOS){
            cnt_primos;
            primos[cnt_primos] = d;
            logaritmo[cnt_primos] = log2(d);
            cnt_primos++;
        }
 
        for(int i = d; i <= MX; i += d){
            divisores[i].pb(d);
        }
    }
}
 
ll eleva(ll a, ll exponente){
    ll ret = 1;
    while(exponente > 0){
        if(exponente & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        exponente >>= 1;
    }
    return ret;
}
 
ld f(int idx, int n){
    if(n == 1){
        return 0;
    }
 
    if(calc[idx][n]) return dp[idx][n];
    calc[idx][n] = true;
 
    ld mejor;
    int quien = -1;
 
    for(int d : divisores[n]){
        ld aux = d - 1;
        aux *= logaritmo[idx];
 
        aux += f(idx + 1, n / d);
 
        if(quien == -1 || le(aux, mejor)){
            mejor = aux;
            quien = d;
        }
    }
 
    dp[idx][n] = mejor;
    sol[idx][n] = quien;
    return mejor;
}
 
ll reconstruye(int idx, int n){
    if(n == 1){
        return 1;
    }
 
    int d = sol[idx][n];
 
    ll ret = eleva(primos[idx], d - 1);
    ret = (ret * reconstruye(idx + 1, n / d) ) % MOD;
    return ret;
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    init();
 
    int n;
    cin >> n;
 
    f(1, n);
 
    cout << reconstruye(1, n) << endl;
 
    return 0;
}