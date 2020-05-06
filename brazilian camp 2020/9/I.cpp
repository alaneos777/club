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

const int MX = 100;
const ld eps = 1e-9;

const char ABAJO_ARRIBA = '|';
const char ARRIBA_DER = 'L';
const char ABAJO_DER = 'r';
const char IZQ_DER = '-';
const char IZQ_ABAJO = '7';
const char IZQ_ARRIBA = 'J';
const char CRUZ = '+';

char mapa[MX + 2][MX + 2];
bool bloqueado[MX + 2][MX + 2];

int tipo[MX + 2][MX + 2];

bool es_primo(int x){
    for(ll d = 2; d * d <= x; d++){
        if(x % d == 0) return false;
    }
    return true;
}

void matate(){
    cout << "NO" << endl;
    exit(0);
}

void resuelve(int n, int m){
    for(int i = n; i >= 1; i--){
        bool b_izq = true;
        for(int j = 1; j <= m; j++){
            bool b_abajo = bloqueado[i + 1][j];
            if(mapa[i][j] == '#'){
                if(!b_izq || !b_abajo) matate();
                bloqueado[i][j] = true;
                b_izq = true;
            }else{
                if(b_izq && b_abajo){
                    // caso 1
                    if(tipo[i][j] != 3) matate();

                    mapa[i][j] = ARRIBA_DER;
                    bloqueado[i][j] = false;
                    b_izq = false;
                }else if(b_izq && !b_abajo){
                    // caso 2
                    if(tipo[i][j] == 1){
                        mapa[i][j] = ABAJO_ARRIBA;
                        bloqueado[i][j] = false;
                        b_izq = true;
                    }else if(tipo[i][j] == 2){
                        matate();
                    }else{
                        mapa[i][j] = ABAJO_DER;
                        bloqueado[i][j] = true;
                        b_izq = false;
                    }
                }else if(!b_izq && b_abajo){
                    // caso 3
                    if(tipo[i][j] == 1){
                        mapa[i][j] = IZQ_DER;
                        bloqueado[i][j] = true;
                        b_izq = false;
                    }else if(tipo[i][j] == 2){
                        matate();
                    }else{
                        mapa[i][j] = IZQ_ARRIBA;
                        bloqueado[i][j] = false;
                        b_izq = true;
                    }
                }else{
                    assert(!b_izq && !b_abajo);
                    // caso 4
                    if(tipo[i][j] == 1) matate();

                    if(tipo[i][j] == 2){
                        bloqueado[i][j] = false;
                        b_izq = false;
                    }else{
                        mapa[i][j] = IZQ_ABAJO;
                        bloqueado[i][j] = true;
                        b_izq = true;
                    }
                }
            }
        }
        if(!b_izq) matate();
    }

    for(int j = 1; j <= m; j++){
        if(!bloqueado[1][j]) matate();
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
             cin >> mapa[i][j];
             if(mapa[i][j] == ABAJO_ARRIBA) tipo[i][j] = 1;
             else if(mapa[i][j] == IZQ_DER) tipo[i][j] = 1;
             else if(mapa[i][j] == CRUZ) tipo[i][j] = 2;
             else tipo[i][j] = 3;
        }
    }
    for(int j = 1; j <= m; j++){
        bloqueado[n + 1][j] = true;
    }
    for(int i = 1; i <= n; i++){
        bloqueado[i][0] = true;
        bloqueado[i][m + 1] = true;
    }

    resuelve(n, m);

    cout << "YES" << endl;
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
             cout << mapa[i][j];
        } cout << endl;
    }

    return 0;
}

