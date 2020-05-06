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

const int MX = 2000;
const ld eps = 1e-9;

int dp[MX + 2][MX + 2];
bool calc[MX + 2][MX + 2];

map<string, int> mapeo;
int cnt_cadenas;

vi hijos[MX + 2];

bool es_raiz[MX + MX + 22];

int pos_arr[MX + 2];
int menor_sub[MX + 2];

void matate(){
    cout << -1 << endl;
    exit(0);
}

int f(int nodo, int pos){
    if(calc[nodo][pos]) return dp[nodo][pos];
    calc[nodo][pos] = true;

    int quitar;

    quitar = 1;
    for(int sig : hijos[nodo]) quitar += f(sig, pos);

    int no_quitar = quitar;

    if(pos_arr[nodo] > pos){
        // puedo decidir no quitar
        no_quitar = 0;
        for(int sig : hijos[nodo]) no_quitar += f(sig, max(pos_arr[nodo], pos));
    }

    dp[nodo][pos] = min(quitar, no_quitar);
    return dp[nodo][pos];
}

void dfs(int nodo){
    menor_sub[nodo] = pos_arr[nodo];
    for(int sig : hijos[nodo]){
        if(menor_sub[sig] != 0) matate();
        dfs(sig);
        menor_sub[nodo] = min(menor_sub[nodo], menor_sub[sig]);
    }
}

int obt_idx(const string& S){
    if(mapeo.find(S) == mapeo.end()){
        cnt_cadenas++;
        mapeo[S] = cnt_cadenas;
    }
    return mapeo[S];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    string linea;

    int cnt = 0;
    int num = 0;
    int raices = 0;
    while(getline(cin, linea)){
        if(cnt % 3 == 0){
            num++;

            int pos = linea.find('(');
            int padre = -1;
            if(pos != string::npos){
                // hay padre
                int fin = linea.find(')');
                padre = obt_idx(linea.substr(pos + 1, fin - pos - 1));
            }else{
                // no hay padre
                pos = linea.find(':');
            }
            int yo = obt_idx(linea.substr(6, pos - 6));

            pos_arr[yo] = num;

            if(padre == -1){
                raices++;
                es_raiz[yo] = true;
            }else{
                hijos[padre].pb(yo);
            }
        }
        cnt++;
    }

    if(cnt_cadenas == 0){
        cout << 0 << endl;
        return 0;
    }

    if(raices == 0) matate();

    int res = 0;

    for(int i = 1; i <= cnt_cadenas; i++){
        if(es_raiz[i]){
            dfs(i);
            res += f(i, 0);
        }
    }

    for(int i = 1; i <= cnt_cadenas; i++) if(menor_sub[i] == 0) matate();
    cout << res << endl;
    return 0;
}
 
