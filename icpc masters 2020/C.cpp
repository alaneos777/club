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

struct ESTADO{
    int acc;
    int pos[MX];
    ESTADO(){
        acc = 0;
        forn(i, MX) pos[i] = i;
    }
    const bool operator < (const ESTADO& otro) const{
        return acc > otro.acc;
    }
};

int dist[MX][MX][MX][MX][MX][MX][MX][MX];

int valores[MX];
int arr_final[2][4];

int& obt_dist(const ESTADO& A){
    return dist[A.pos[0]][A.pos[1]][A.pos[2]][A.pos[3]][A.pos[4]][A.pos[5]][A.pos[6]][A.pos[7]];
}

bool es_solucion(const ESTADO& A){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            int idx = A.pos[4 * i + j];
            if(valores[idx] != arr_final[i][j]) return false;
        }
    }
    return true;
}

priority_queue<ESTADO> cola;
int dijkstra(){
    ESTADO act, otro;
    cola.push(act);
    obt_dist(act) = 0;
    while(!cola.empty()){
        act = cola.top(); cola.pop();
        int D = obt_dist(act);
        if(act.acc > D) continue;
        if(es_solucion(act)) return D;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 4 - 1; j++){
                // swap con la derecha
                otro = act;
                int izq = 4 * i + j, der = izq + 1;
                swap(otro.pos[izq], otro.pos[der]);
                otro.acc = D + valores[act.pos[izq]] + valores[act.pos[der]];
                int& d = obt_dist(otro);
                if(d == -1 || otro.acc < d){
                    d = otro.acc;
                    cola.push(otro);
                }
            }
        }
        for(int j = 0; j < 4; j++){
            // swap hacia abajo
            otro = act;
            int izq = j, der = 4 + j;
            swap(otro.pos[izq], otro.pos[der]);
            otro.acc  = D + valores[act.pos[izq]] + valores[act.pos[der]];
            int& d = obt_dist(otro);
            if(d == -1 || otro.acc < d){
                d = otro.acc;
                cola.push(otro);
            }
        }
    }
    return -1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for(int i = 0; i < 8; i++) cin >> valores[i];
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 4; j++)
            cin >> arr_final[i][j];
    memset(dist, -1, sizeof(dist));
    cout << dijkstra() << endl;
    return 0;
}

