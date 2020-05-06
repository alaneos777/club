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
const int INF = 1e9 + 7;
 
int arr[4 * MX + 2];
int v[MX + 2];
 
struct Seg{
    int desde, hasta;
    Seg *izq, *der;
    int menor;
 
    Seg(int i, int d) : desde(i), hasta(d), menor(-1), izq(NULL), der(NULL) {}
 
    void build(){
        if(desde >= hasta){
            menor = arr[desde];
        }else{
            int mitad = (desde + hasta) / 2;
            izq = new Seg(desde, mitad);
            der = new Seg(mitad + 1, hasta);
 
            izq->build();
            der->build();
 
            if(v[izq->menor] < v[der->menor]) menor = izq->menor;
            else menor = der->menor;
        }
    }
 
    void update(int pos, int val){
        if(desde > pos || hasta < pos) return;
 
        if(desde >= hasta){
            v[menor] = val;
        }else{
            izq->update(pos, val);
            der->update(pos, val);
            if(v[izq->menor] < v[der->menor]) menor = izq->menor;
            else menor = der->menor;
        }
    }
    int query(int ri, int rf){
        if(desde > rf || hasta < ri) return -1;
        if(desde >= ri && hasta <= rf) return menor;
 
        int nodo1 = izq->query(ri, rf);
        int nodo2 = der->query(ri, rf);
 
        if(nodo1 == -1) return nodo2;
        if(nodo2 == -1) return nodo1;
        if(v[nodo1] < v[nodo2]) return nodo1;
        return nodo2;
    }
};
 
vi hijos[MX + 2];
 
int ini_seq[MX + 2];
int fin_seq[MX + 2];
int cnt_seq;
 
int sub[MX + 2];
 
Seg *tree;
 
bool impreso[MX + 2];
 
void dfs(int nodo){ 
    sub[nodo] = 1;
 
    cnt_seq++;
    arr[cnt_seq] = nodo;
 
    ini_seq[nodo] = cnt_seq;
 
    for(int sig : hijos[nodo]){
        dfs(sig);
        sub[nodo] += sub[sig];
    }
 
    fin_seq[nodo] = cnt_seq;
}
 
void procesa(int nodo){
    int l = ini_seq[nodo];
    int r = fin_seq[nodo];
    
    tree->update(l, INF);
 
    while(true){
        int sig = tree->query(l, r);
        if(v[sig] == INF) break;
        procesa(sig);
    }
    assert(!impreso[nodo]);
    impreso[nodo] = true;
    cout << nodo << " ";
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int n;
    cin >> n;
 
    for(int i = 2; i <= n; i++){
        int p;
        cin >> p;
        hijos[p].pb(i);
    }
 
    for(int i = 1; i <= n; i++) cin >> v[i];
 
    dfs(1);
 
    tree = new Seg(1, fin_seq[1]);
    tree->build();
    
    procesa(1);
    cout << endl;
 
    return 0;
}