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
 
const int PUNTO = 0;
const int DIAG = 1;
 
int original;
 
void reemplaza(string& S){
    int n = S.size();
    forn(i, n){
        if(S[i] == '.'){
            original = PUNTO;
            S[i] = '*';
        }
        if(S[i] == '/'){
            original = DIAG;
            S[i] = '*';
        }
    }
}
 
void agrega(string& dest, int& idx, const string& S, int n){
    int pos = idx;
    while(pos < n && S[pos] != '*') pos++;
    while(idx < pos){
        dest += S[idx];
        idx++;
    }
}
 
string resuelve(const string& S, string sep, int tipo){
    string pt1 = "";
    string pt2 = "";
    string pt3 = "";
 
    int n = S.size();
 
    int idx = 0;
    agrega(pt1, idx, S, n);
    idx++;
    agrega(pt2, idx, S, n);
    idx++;
    agrega(pt3, idx, S, n);
 
    while(pt1.size() < 2) pt1 = "0" + pt1;
    while(pt2.size() < 2) pt2 = "0" + pt2;
    while(pt3.size() < 4) pt3 = "0" + pt3;
 
    string ret;
    
    if(tipo == original) ret = pt1 + sep + pt2;
    else ret = pt2 + sep + pt1;
 
    ret += sep + pt3;
    return ret;
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int n;
    cin >> n;
 
    forn(i, n){
        string cadena;
        cin >> cadena;
 
        reemplaza(cadena);
 
        string dos = resuelve(cadena, "/", DIAG);
        string uno = resuelve(cadena, ".", PUNTO);
        cout << uno << " " << dos << endl;
    }
 
    return 0;
}
