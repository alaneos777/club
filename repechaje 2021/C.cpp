#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; ++i)
#define rep(i, a, b) for(int i = a; i < b; ++i)
#define eb emplace_back
#define pb push_back
#define fi first
#define se second
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

const int MX = 8;
const int INF = 1e9;

const char BORRADO = '#';

char mapa[MX + 2][MX + 2];
int N, M;
int T;

int min_resp = INF;

int total_letras_fila[MX + 2][300 + 2];
int total_letras_col[MX + 2][300 + 2];

int letras_fila[MX + 2][300 + 2]; // letras_fila[fila][letra]
int letras_col[MX + 2][300 + 2]; // letras_col[col][letra]

int act_resp = 0;

void busqueda(int i, int j){
    if(act_resp > min_resp) return;
    if(i > N){
        assert(act_resp <= min_resp);
        min_resp = act_resp;
        return;
    }
    if(j > M){
        busqueda(i + 1, 1);
        return;
    }
    char c = mapa[i][j];
    if(total_letras_fila[i][c] <= 1 && total_letras_col[j][c] <= 1){
        // no me conviene nunca quitar esta celda
        busqueda(i, j + 1);
        return;
    }

    if(letras_fila[i][c] == 0 && letras_col[j][c] == 0){
        // no borrar
        letras_fila[i][c]++;
        letras_col[j][c]++;
        busqueda(i, j + 1);
        letras_fila[i][c]--;
        letras_col[j][c]--;
    }

    // borrar
    if(mapa[i - 1][j] != BORRADO &&
       mapa[i][j + 1] != BORRADO &&
       mapa[i + 1][j] != BORRADO &&
       mapa[i][j - 1] != BORRADO){
       mapa[i][j] = BORRADO;
       act_resp++;
       busqueda(i, j + 1);
       act_resp--;
       mapa[i][j] = c;
    }
    
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> M >> N;

    cin >> T;

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            char c;
            cin >> c;
            mapa[i][j] = c;
            total_letras_fila[i][c]++;
            total_letras_col[j][c]++;
        }
    }

    busqueda(1, 1);
    assert(min_resp < INF);

    cout << min_resp << endl;

    return 0;
}

