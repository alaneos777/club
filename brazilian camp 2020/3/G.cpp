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
 
const int MX = 60;
 
const ll INF = 1e18;
 
string cad;
 
int n;
 
string solucion;
 
ll dp[MX + 2][MX + 2][MX + 2][2];
bool calc[MX + 2][MX + 2][MX + 2][2];
 
ll f(int idx, int A, int S, bool b){
    if(idx == n){
        if(S < A) return 0;
        if(A == 0 && S == 0) return 1;
    }
 
    if(calc[idx][A][S][b]) return dp[idx][A][S][b];
    calc[idx][A][S][b] = true;
 
    ll res = 0;
 
    if(idx < n && (!b || cad[idx] != '-')) res += f(idx + 1, A, S, (cad[idx] == '-'));
    if(S > 0) res += f(idx, A + 1, S - 1, false);
    if(S > 0 && A > 0) res += f(idx, A - 1, S - 1, false);
 
    if(res < 0 || res > INF) res = INF;
 
    dp[idx][A][S][b] = res;
    return res;
}
 
void matate(){
    cout << "Overflow" << endl;
    exit(0);
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    cin >> cad;
    n = cad.size();
 
    ll k;
    cin >> k;
 
    int idx = 0;
    int A = 0;
    int S = 0;
    bool b = false;
 
    forn(i, n-1) if(cad[i] == '-' && cad[i + 1] == '-') S++;
    S = (S + 1) / 2;
    S = 2 * S;
 
    ll aux;
 
    while(idx < n || S > 0){
        // dejarlo asi
        if(idx < n && (!b || cad[idx] != '-')){
            aux = f(idx + 1, A, S, (cad[idx] == '-'));
            if(aux >= k){
                solucion += cad[idx];
 
                b = (cad[idx] == '-');
                idx++;
 
                continue;
            }else{
                k -= aux;
            }
        }
 
        // abrir
        if(S > 0){
            aux = f(idx, A + 1, S - 1, false);
            if(aux >= k){
                solucion += "{";
 
                A++;
                S--;
                b = false;
 
                continue;
            }else{
                k -= aux;
            }
        }
 
        // cerrar
        if(A > 0 && S > 0){
            aux = f(idx, A - 1, S - 1, false);
            if(aux >= k){
                solucion += "}";
                A--;
                S--;
                b = false;
 
                continue;
            }else{
                k -= aux;
            }
        }
 
        matate();
    }
 
    cout << solucion << endl;
 
    return 0;
}