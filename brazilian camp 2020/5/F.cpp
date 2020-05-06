#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
using namespace std;
 
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;
 
const int MX = 1e5;
const ld eps = 1e-9;
 
const ll MOD = 1e9 + 7;
 
char palo[MX + 2];
 
ll pot[MX + 2];
 
ll f(int n, char P){
    if(n == 0) return 0;
    if(palo[n] == P) return f(n - 1, P);
 
    char cubeta[3] = {0, 0, 0};
 
    cubeta[palo[n] - 'A']++;
    cubeta[P - 'A']++;
 
    int aux = 0;
    while(cubeta[aux] > 0) aux++;
 
    ll res = f(n - 1, aux + 'A');
    res = (res + pot[n - 1]) % MOD;
    return res;
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    pot[0] = 1;
    for(int i = 1; i <= MX; i++) pot[i] = (pot[i - 1] << 1) % MOD;
 
    int n;
    cin >> n;
 
    for(int i = 1; i <= n; i++){
        cin >> palo[i];
    }
 
    cout << f(n, 'B') << endl;
 
    return 0;
}
