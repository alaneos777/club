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
 
int g(int n){
    if(n == 1) return 0;
    if(n == 2) return 1;
    if(n == 3) return 2;
    return 1 + g(n - 3);
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int n, s, f;
    cin >> n >> s >> f;
 
    if(s == f){
        cout << -1 << endl;
        return 0;
    }
 
    if(s > f) swap(s, f);
 
    int d = f - s;
 
    int res;
    
    if(d == 1){
        if(s == 1) res = 1;
        else if(f == n) res = 1;
        else res = -1;
    }else{
        if(s == 1 && f == n){
            // caso 3
            res = g(d + 1);
        }else{
            if(s == 1){
                // caso 1
                res = 1 + g(d);
            }else if(f == n){
                // caso 2
                res = 1 + g(d);
            }else{
                // caso 4
                res = 2 + g(d - 1);
            }
        }
    }
    cout << res << endl;
 
    return 0;
}
