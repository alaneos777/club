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
 
const int MX = 1000;
 
pii sig[MX + 2][MX + 2];
 
int bien = 2;
 
string cad_query;
 
int tiempo;
 
void f(int m, int n){
    int col = (n + 1) / 2;
 
    if(n == 2){
        if(tiempo & 1){
            // derecha
            cad_query += "R";
            forn(i, m - 1) cad_query += "D";
        }else{
            // abajo
            forn(i, m - 1) cad_query += "D";
            cad_query += "R";
        }
        return;
    }
 
    forn(i, col - 1) cad_query += "R";
    forn(i, m - 1) cad_query += "D";
    forn(i, n - col) cad_query += "R";
}
 
void construye_query(int m, int n){
    tiempo++;
    cad_query = "";
    pii act(1, 1);
 
    pii ultimo(m, n);
 
    do{
        pii otro = sig[act.fi][act.se];
        int m_prima = otro.fi - act.fi + 1;
        int n_prima = otro.se - act.se + 1;
 
        f(m_prima, n_prima);
 
        act = otro;
    }while(act != ultimo);
}
 
void haz_query(int m, int n){
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            sig[i][j] = pii(0, 0);
        }
    }
 
    cout << "? " << cad_query << endl;
    cout.flush();
 
    cin >> bien;
    int fila, columna;
    cin >> fila >> columna;
 
    assert(fila == 1 && columna == 1);
    pii ant(fila, columna);
    forn(kk, bien - 1){
        cin >> fila >> columna;
        sig[ant.fi][ant.se] = pii(fila, columna);
        ant = pii(fila, columna);
    }
    assert(ant.fi == m && ant.se == n);
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int n, m;
    cin >> m >> n;
 
    sig[1][1] = pii(m, n);
 
    for(int i = 0; i < 10; i++){
        construye_query(m, n);
        haz_query(m, n);
    }
    construye_query(m, n);
    cout << "! " << cad_query << endl;
    cout.flush();
 
    return 0;
}