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
 
    int n;
    cin >> n;
 
    int sum = 0;
    int menor = 1e9;
 
    forn(i, n){
        int A;
        cin >> A;
        if(A % 2 == 0) A--;
        if(A < menor) menor = A;
 
        sum += A;
    }
 
    if(n % 2 == 0) sum -= menor;
    cout << sum << endl;
    return 0;
}