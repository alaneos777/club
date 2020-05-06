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
const int MAXLOG = 20;
 
struct OPERACION{
    int dist;
    int color;
    int tiempo;
 
    const bool operator < (const OPERACION& otro) const{
        if(dist == otro.dist){
            if(color == otro.color) return tiempo < otro.tiempo;
            return color < otro.color;
        }
        return dist < otro.dist;
    }
};
 
int peso_raiz[MX + 2];
int nivel[MX + 2];
int padre_saltos[MX + 2][MAXLOG + 2];
 
vi rel[MX + 2];
vi peso[MX + 2];
 
int LCA(int a, int b){
    if(nivel[a] > nivel[b]) swap(a, b);
 
    for(int j = MAXLOG; j >= 0; j--){
        if(padre_saltos[b][j] == -1) continue;
        if(nivel[padre_saltos[b][j]] >= nivel[a]){
            b = padre_saltos[b][j];
        }
    }
 
    if(a == b) return a;
 
    for(int j = MAXLOG; j >= 0; j--){
        if(padre_saltos[a][j] == -1) continue;
        if(padre_saltos[a][j] == padre_saltos[b][j]) continue;
        a = padre_saltos[a][j];
        b = padre_saltos[b][j];
    }
    return padre_saltos[a][0];
}
 
int calc_distancia_nodos(int a, int b){
    int C = LCA(a, b);
    int ret = 0;
    ret += peso_raiz[a] - peso_raiz[C];
    ret += peso_raiz[b] - peso_raiz[C];
    return ret;
}
 
void dfs_saltos(int nodo){
    int tam = rel[nodo].size(), sig;
    for(int i = 0; i < tam; i++){
        sig = rel[nodo][i];
        if(sig == padre_saltos[nodo][0]) continue;
        padre_saltos[sig][0] = nodo;
        nivel[sig] = nivel[nodo] + 1;
        peso_raiz[sig] = peso_raiz[nodo] + peso[nodo][i];
        dfs_saltos(sig);
    }
}
 
void init_saltos(int N){
    for(int j = 0; j <= MAXLOG; j++){
        for(int i = 1; i <= N; i++){
            padre_saltos[i][j] = -1;
        }
    }
    padre_saltos[1][0] = -1;
    nivel[1] = 0;
    peso_raiz[1] = 0;
    dfs_saltos(1);
 
    for(int j = 1; j <= MAXLOG; j++){
        for(int i = 1; i <= N; i++){
            int sig = padre_saltos[i][j - 1];
            if(sig != -1) sig = padre_saltos[sig][j - 1];
            padre_saltos[i][j] = sig;
        }
    }
}
 
bool muerto[MX + 2];
int padre_c[MX + 2];
int dist_padre_c[MX + 2];
 
int sub[MX + 2];
 
void dfs_centroide(int nodo, int padre){
    sub[nodo] = 1;
    for(int sig : rel[nodo]){
        if(sig == padre) continue;
        if(muerto[sig]) continue;
 
        dfs_centroide(sig, nodo);
        sub[nodo] += sub[sig];
    }
}
 
int busca_centroide(int nodo, int padre, int total){
    for(int sig : rel[nodo]){
        if(sig == padre) continue;
        if(muerto[sig]) continue;
 
        if(2 * sub[sig] > total){
            return busca_centroide(sig, nodo, total);
        }
    }
    return nodo;
}
 
int construye_centroide(int nodo){
    dfs_centroide(nodo, -1);
    nodo = busca_centroide(nodo, -1, sub[nodo]);
 
    muerto[nodo] = true;
 
    padre_c[nodo] = -1;
 
    for(int sig : rel[nodo]){
        if(muerto[sig]) continue;
        int r = construye_centroide(sig);
        padre_c[r] = nodo;
        dist_padre_c[r] = calc_distancia_nodos(r, nodo);
    }
    return nodo;
}
 
vector<OPERACION> pila[MX + 2];
 
void update(int nodo, int d, int c, int t){
    if(d < 0) return;
    while(!pila[nodo].empty() && pila[nodo].back().dist <= d){
        pila[nodo].pop_back();
    }
    OPERACION OP;
    OP.dist = d;
    OP.color = c;
    OP.tiempo = t;
    pila[nodo].push_back(OP);
}
 
void update_tree(int nodo, int d, int c, int t){
    int inicial = nodo;
    do{
        update(nodo, d - calc_distancia_nodos(inicial, nodo), c, t);
        nodo = padre_c[nodo];
    }while(nodo != -1);
}
 
void aplica_op(int nodo, int d, int& res, int &t){
    if(pila[nodo].empty()) return;
 
    OPERACION OP;
    OP.dist = d;
    OP.color = -1;
    OP.tiempo = -1;
 
    int pos = lower_bound(pila[nodo].rbegin(), pila[nodo].rend(), OP) - pila[nodo].rbegin();
    int tam = pila[nodo].size();
    if(pos == tam) return;
 
    OP = pila[nodo][tam - 1 - pos];
    if(OP.tiempo < t) return;
    t = OP.tiempo;
    res = OP.color;
}
 
int query_tree(int nodo){
    int inicial = nodo;
    int res = 0;
    int t = 0;
    do{
        int d = calc_distancia_nodos(inicial, nodo);
        aplica_op(nodo, d, res, t);
        nodo = padre_c[nodo];
    }while(nodo != -1);
    return res;
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int N;
    cin >> N;
 
    for(int i = 1; i < N; i++){
        int a, b, w;
        cin >> a >> b >> w;
        rel[a].pb(b);
        rel[b].pb(a);
 
        peso[a].pb(w);
        peso[b].pb(w);
    }
 
    init_saltos(N);
 
    construye_centroide(1);
 
    int Q;
    cin >> Q;
    for(int t = 1; t <= Q; t++){
        int tipo;
        cin >> tipo;
        if(tipo == 1){
            int v, d, c;
            cin >> v >> d >> c;
            update_tree(v, d, c, t);
        }else{
            int v;
            cin >> v;
            cout << query_tree(v) << endl;
        }
    }
 
    return 0;
}
