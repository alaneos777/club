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

string S;

ll lee_num(int l, int r){
    ll ret = 0;
    ll fact = 1;
    ll niv = 2;
    for(int i = r; i >= l; i--){
        ll digito = 0;
        if(S[i] >= '0' && S[i] <= '9'){
            digito = S[i] - '0';
        }else{
            digito = 10 + tolower(S[i]) - 'a';
        }
        ret += digito * fact;
        fact *= niv;
        niv++;
    }
    return ret;
}

void convierte(ll num){
    ll fact = 1;
    ll niv = 1;
    while(num >= fact){
        niv++;
        fact *= niv;
    }
    fact /= niv;
    niv--;
    while(niv >= 1){
        ll digito = num / fact;
        // Imprime digito
        if(digito < 10){
            cout << digito;
        }else{
            cout << (char)(digito - 10 + 'A');
        }
        num %= fact;
        fact /= niv;
        niv--;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> S;
    int N = S.size();

    ll ret = 0;
    int i = 0;
    char op = '+';
    while(i < N){
        int j = i;
        while(j < N && S[j] != '+' && S[j] != '-') j++;
        ll aux = lee_num(i, j - 1);
        if(op == '+') ret += aux;
        else ret -= aux;
        if(j < N) op = S[j];
        i = j + 1;
    }
    convierte(ret);
    cout << endl;

    return 0;
}
