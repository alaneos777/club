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
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    ll n;
    cin >> n;
 
    ll mitad = (n - 1LL) / 2LL;
    ll resp = n * mitad;
 
    ll quitar = 0;
    if(n % 3LL == 0) quitar = (n / 3LL) * 2;
 
    resp -= quitar;
    cout << resp << endl;
 
    return 0;
}
