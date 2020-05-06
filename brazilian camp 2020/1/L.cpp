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
 
map<ll, ll> cubeta;
 
int a[MX + 2];
 
void agrega(int v){
    if(cubeta.find(v) == cubeta.end()){
        cubeta[v] = 1;
    }else cubeta[v]++;
}
 
void quita(int v){
    cubeta[v]--;
    if(cubeta[v] == 0) cubeta.erase(v);
}
 
void reemplaza(int idx, int inc){
    quita(a[idx]);
    a[idx] += inc;
    agrega(a[idx]);
}
 
ll solucion(){
    map<ll, ll>::iterator it = cubeta.end();
    it--;
    return it->second * it->first;
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int n;
    cin >> n;
 
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        agrega(a[i]);
    }
 
    ll menor = solucion();
 
    for(int i = 1; i <= n; i++){
        if(a[i] == 0) continue;
 
        reemplaza(i, -1);
 
        // checa izq
        if(i > 1){
            reemplaza(i - 1, 1);
            menor = min(menor, solucion());
            reemplaza(i - 1, -1);
        }
 
        // checa der
        if(i < n){
            reemplaza(i + 1, 1);
            menor = min(menor, solucion());
            reemplaza(i + 1, -1);
        }
 
        reemplaza(i, 1);
    }
 
    cout << menor << endl;
 
    return 0;
}