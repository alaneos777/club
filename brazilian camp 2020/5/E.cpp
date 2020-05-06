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
const ld eps = 1e-9;
 
int near(int n){
    int ans = 1;
    while(ans < n) ans *= 2;
    return ans;
}
 
void fwt(vector<int> & a){
    int n = a.size();
    for(int k = 1; k < n; k <<= 1){
        for(int i = 0; i < n; i += k<<1){
            for(int j = 0; j < k; ++j){
                a[i+j+k] ^= a[i+j];
            }
        }
    }
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a;
    for(char c : s){
        if(c == '+') a.pb(0);
        else a.pb(1);
    }
    a.resize(near(n));
    fwt(a);
    string t;
    for(int i = 0; i < n; ++i){
        if(a[i] == 0) t += "+";
        else t += "-";
    }
    cout << t << "\n";
    return 0;
}