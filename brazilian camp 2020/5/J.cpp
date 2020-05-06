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
 
const int TIPO_A = 0;
const int TIPO_C = 1;
const int TIPO_B = 2;
 
int sub[MX + 2];
int padre[MX + 2];
vi rel[MX + 2];
 
set<int> indices[MX + 2];
 
int ini_seq[MX + 2];
int fin_seq[MX + 2];
int cnt_seq;
 
int seq_2_nodo[MX + 2];
 
char letra[MX + 2];
int visitado[MX + 2];
 
void dfs_sol(int nodo, char c){
    if(visitado[nodo]) return;
    visitado[nodo] = true;
 
    letra[nodo] = c;
 
    for(int sig : rel[nodo]){
        if(letra[sig] != 0) continue;
        dfs_sol(sig, c);
    }
}
 
void agrega_a_lista(int nodo){
    indices[sub[nodo]].insert(ini_seq[nodo]);
}
 
void elimina_de_lista(int nodo){
    indices[sub[nodo]].erase(ini_seq[nodo]);
}
 
int n;
int max_A;
int nodo_1, nodo_2;
int tipo_1, tipo_2;
 
int mex(int t1, int t2){
    if(t1 == t2) return TIPO_C;
    return TIPO_A;
}
 
char tipo_2_letra(int t){
    if(t == TIPO_A) return 'A';
    if(t == TIPO_B) return 'B';
    return 'C';
}
 
bool es_ancestro(int nodo_sup, int nodo){
    int idx = ini_seq[nodo];
    if(idx < ini_seq[nodo_sup] || idx > fin_seq[nodo_sup]) return false;
    return true;
}
 
void acomoda_solucion(){
    int t3 = mex(tipo_1, tipo_2);
 
    if(tipo_1 == TIPO_A) tipo_1 = TIPO_B;
    else if(tipo_2 == TIPO_A) tipo_2 = TIPO_B;
    
    letra[nodo_1] = tipo_2_letra(tipo_1);
    letra[nodo_2] = tipo_2_letra(tipo_2);
 
    if(es_ancestro(nodo_1, nodo_2)){
        letra[padre[nodo_2]] = letra[nodo_1];
        letra[padre[nodo_1]] = tipo_2_letra(t3);
        return;
    }
    if(es_ancestro(nodo_1, nodo_2)){
        letra[padre[nodo_1]] = letra[nodo_2];
        letra[padre[nodo_2]] = tipo_2_letra(t3);
        return;
    }
    letra[padre[nodo_1]] = tipo_2_letra(t3);
    letra[padre[nodo_2]] = tipo_2_letra(t3);
}
 
int busca_fuera(int nodo, int tam){
    // busca fuera del subarbol de nodo, -1 si no hay nodo
    if(indices[tam].empty()) return -1;
 
    set<int>::iterator it = indices[tam].begin();
 
    int idx = *it;
    if(idx < ini_seq[nodo] || idx > fin_seq[nodo]) return seq_2_nodo[idx];
 
    it = indices[tam].upper_bound(fin_seq[nodo]);
    if(it == indices[tam].end()) return -1;
 
    idx = *it;
    return seq_2_nodo[idx];
}
 
int busca_dentro(int nodo, int tam){
    // busca dentro del subarbol de nodo, -1 si no hay nodo
    if(indices[tam].empty()) return -1;
 
    set<int>::iterator it = indices[tam].lower_bound(ini_seq[nodo]);
    if(it == indices[tam].end()) return -1;
 
    int idx = *it;
    if(idx > fin_seq[nodo]) return -1;
 
    return seq_2_nodo[idx];;
}
 
void actualiza_sol(int n1, int n2, int t1, int t2, int tamA){
    if(tamA > max_A){
        max_A = tamA;
        nodo_1 = n1;
        nodo_2 = n2;
        tipo_1 = t1;
        tipo_2 = t2;
    }
}
 
void caso_1(int nodo){
    // sub[nodo] == A
    int tamA = sub[nodo];
    int tamC = n - 2 * tamA;
 
    if(tamC < 1) return;
 
    int otro;
    // Busca un tamA
    otro = busca_fuera(nodo, tamA);
    if(otro != -1) actualiza_sol(nodo, otro, TIPO_A, TIPO_A, tamA);
 
    // Busca un tamC
    otro = busca_fuera(nodo, tamC);
    if(otro != -1) actualiza_sol(nodo, otro, TIPO_A, TIPO_C, tamA);
}
 
void caso_2(int nodo){
    // sub[nodo] == C
    int tamC = sub[nodo];
    int tamA = n - tamC;
 
    if(tamA < 1) return;
    if(tamA & 1) return;
    tamA /= 2;
 
    int otro;
    // Busca un tamA
    otro = busca_fuera(nodo, tamA);
    if(otro != -1) actualiza_sol(nodo, otro, TIPO_C, TIPO_A, tamA);
}
 
void caso_3(int nodo){
    // sub[nodo] == 2A
    if(sub[nodo] & 1) return;
    int tamA = sub[nodo] / 2;
    int tamC = n - sub[nodo];
 
    if(tamC < 1) return;
 
    int otro;
    // Busca un tamA dentro
    otro = busca_dentro(nodo, tamA);
    if(otro != -1) actualiza_sol(nodo, otro, TIPO_A, TIPO_A, tamA); 
}
 
void caso_4(int nodo){
    // sub[nodo] == A + C
    int tamA = n - sub[nodo];
    int tamC = sub[nodo] - tamA;
    if(tamC < 1) return;
 
    int otro;
    // Busca un tamA dentro
    otro = busca_dentro(nodo, tamA);
    if(otro != -1) actualiza_sol(nodo, otro, TIPO_C, TIPO_A, tamA);
 
    otro = busca_dentro(nodo, tamC);
    if(otro != -1) actualiza_sol(nodo, otro, TIPO_A, TIPO_C, tamA);
}
 
void resuelve(int nodo){
    elimina_de_lista(nodo);
 
    // Asume sub[nodo] == A
    caso_1(nodo);
    // Asume sub[nodo] == C
    caso_2(nodo);
    // Asume sub[nodo] == 2A
    caso_3(nodo);
    // Asume sub[nodo] == A + C
    caso_4(nodo);
 
    for(int sig : rel[nodo]){
        if(sig == padre[nodo]) continue;
        resuelve(sig);
    }
    
    agrega_a_lista(nodo);
}
 
void dfs1(int nodo){
    sub[nodo] = 1;
 
    cnt_seq++;
    ini_seq[nodo] = cnt_seq;
    seq_2_nodo[cnt_seq] = nodo;
 
    for(int sig : rel[nodo]){
        if(sig == padre[nodo]) continue;
        padre[sig] = nodo;
        dfs1(sig);
        sub[nodo] += sub[sig];
    }
    
    fin_seq[nodo] = cnt_seq;
 
    agrega_a_lista(nodo);
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    cin >> n;
 
    forn(i, n - 1){
        int a, b;
        cin >> a >> b;
        rel[a].pb(b);
        rel[b].pb(a);
    }
 
    padre[1] = -1;
    dfs1(1);
 
    resuelve(1);
 
    acomoda_solucion();
 
    for(int i = 1; i <= n; i++){
        if(letra[i] == 0) continue;
        if(visitado[i]) continue;
        dfs_sol(i, letra[i]);
    }
 
    for(int i = 1; i <= n; i++) cout << letra[i];
    cout << endl;
 
    return 0;
}