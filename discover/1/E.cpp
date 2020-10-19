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

const int MX = 1000;

const string SI = "Yes";
const string NO = "No";

int ceros, cienes, otros;

void calc_sobra(int cant){
    int bajan = (cienes + otros);
    int tengo = bajan * 5;
    if(tengo >= cant){
        cout << SI << endl;
    }else{
        cout << NO << endl;
    }
}

void calc_falta(int cant){
    int suben = (ceros + otros);
    int tengo = (suben * 5);
    if(tengo > cant){
        cout << SI << endl;
    }else{
        cout << NO << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int N ;
    cin >> N;
    int sum = 0;
    forn(i, N){
        int a;
        cin >> a;
        sum += a;
        if(a == 0) ceros++;
        else if(a == 100) cienes++;
        else otros++;
    }

    if(sum < 100){
        calc_falta((100 - sum) * 10);
    }else if(sum > 100){
        calc_sobra((sum - 100) * 10);
    }else{
        cout << SI << endl;
    }

    return 0;
}
