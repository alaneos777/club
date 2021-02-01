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

const int MX = 1e5;

int render(const string& linea, int i, char delim, const string& ini, const string& fin){
    cout << ini;
    while(linea[i] != delim)
        cout << linea[i++];
    cout << fin;
    return i;
}

void solve(){
    string linea;
    getline(cin, linea);
    int N = linea.size();
    for(int i = 0; i < N; i++){
        if(linea[i] == '*'){
            i = render(linea, i + 1, '*', "<b>", "</b>");
        }else if(linea[i] == '_'){
            i = render(linea, i + 1, '_', "<i>", "</i>");
        }else cout << linea[i];
    }
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int T;
    cin >> T;
    cin.ignore();
    while(T--)
        solve();

    return 0;
}
