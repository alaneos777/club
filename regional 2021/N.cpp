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
 
int lee_num(){
    int X, Y;
    int a = scanf("$%d.%d", &X, &Y);
    getchar();
    return X * 100 + Y;
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int N;
    scanf("%d", &N);
    getchar();
 
    int act = lee_num();
    int res = 0;
    while(N--){
        int t = lee_num();
        act += t;
        if(act % 100 != 0) res++;
    }
    printf("%d\n", res);
 
    return 0;
}