#include <bits/stdc++.h>

using namespace std;

typedef long long int ull;

ull mcd(ull a, ull b){
    ull r;
    while(b != 0){
        r = a%b;
        a = b, b = r;
    }
    return a;
}

int main(){
    ios_base::sync_with_stdio(0);
    ull n;
    while(true){
        cin >> n;
        if(n == 0) break;
        bool positivo = (n > 0);
        n = abs(n);
        vector< pair<ull, int> > factorizacion;
        for(ull d=2;d<=sqrt(n);d++){
            if(n%d == 0){
                factorizacion.push_back(make_pair(d, 0));
                while(n%d == 0){
                    factorizacion[factorizacion.size()-1].second++;
                    n /= d;
                }
            }
        }
        if(n > 1){
            if(!factorizacion.empty() && factorizacion[factorizacion.size()-1].first == n) factorizacion[factorizacion.size()-1].second++;
            else factorizacion.push_back(make_pair(n, 1));
        }
        int p = factorizacion[0].second;
        for(size_t i=1;i<factorizacion.size();i++){
            if(p == 1) break;
            p = mcd(p, factorizacion[i].second);
        }
        if(!positivo) while(p%2 == 0) p /= 2;
        cout << p << "\n";
    }
    return 0;
}
