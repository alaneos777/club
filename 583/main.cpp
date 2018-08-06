#include <bits/stdc++.h>

using namespace std;

typedef long long int ull;

map<ull, ull> factorizar(ull n){
    map<ull, ull> f;
    if(n==1) return f;
    ull d = 2;
    while(d<=sqrt(n)){
        if(n%d==0){
            f[d]++;
            n/=d;
        }else{
            d++;
        }
    }
    f[n]++;
    return f;
}

int main()
{
    ios_base::sync_with_stdio(0);
    ull n;
    while(true){
        cin >> n;
        if(n==0) break;
        map<ull, ull> f;
        cout << n << " = ";
        if(n>=0){
            f=factorizar(n);
        }else{
            f=factorizar(-n);
            cout << "-1 x ";
        }
        bool flag = false;
        for(pair<ull, ull> p:f){
            for(ull i=1;i<=p.second;i++){
                if(flag){
                    cout << " x ";
                }else{
                    flag = true;
                }
                cout << p.first;
            }
        }
        cout << "\n";
    }
    return 0;
}
