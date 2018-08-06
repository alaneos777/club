#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;

ull cuantos_multiplos(ull p, ull a, ull b){
    return b/p - (a-1)/p;
}

vector<ull> factores_primos(ull n){
    set<ull> primos;
    if(n==1) return {};
    ull d=2;
    while(d<=sqrt(n)){
        if(n%d==0){
            primos.insert(d);
            n /= d;
        }else{
            d++;
        }
    }
    primos.insert(n);
    vector<ull> vec (primos.begin(), primos.end());
    return vec;
}

vector< vector<ull> > productos(vector<ull> arr){
    int n = arr.size();
    int p_n = pow(2, n);
    vector< vector<ull> > ans(n+1);
    for(int i=0;i<p_n;i++){
        int c = 0;
        ull tmp = 1;
        for(int j=0;j<n;j++){
            if(i & (1 << j)){
                tmp *= arr[j];
                c++;
            }
        }
        ans[c].push_back(tmp);
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ull n, a, b;
    cin >> n >> a >> b;
    ull ans = b-a+1;
    int signo = -1;
    vector<ull> tmp=factores_primos(n);
    vector< vector<ull> > p = productos(tmp);
    for(int i=1;i<p.size();i++){
        for(int j=0;j<p[i].size();j++){
            ans += cuantos_multiplos(p[i][j], a, b) * signo;
        }
        signo *= -1;
    }
    cout << ans;
    return 0;
}
