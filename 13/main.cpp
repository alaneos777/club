#include <bits/stdc++.h>

using namespace std;

typedef uint64_t ull;

vector<int> primos;

void criba(int n){
    vector<bool> tmp(n+1, true);
    tmp[1] = false;
    for(int i=2;i*i<=n;i++){
        while(!tmp[i]) i++;
        for(int j=2*i;j<=n;j+=i){
            tmp[j] = false;
        }
    }
    for(int i=1;i<=n;i++){
        if(tmp[i]) primos.push_back(i);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    int maximo = 0;
    cin >> t;
    vector<int> entrada(t);
    for(int i=0;i<t;i++){
        int n;
        cin >> n;
        if(n > maximo) maximo = n;
        entrada[i] = n;
    }
    criba(maximo);
    int l = primos.size();
    map<int, ull> productos;
    for(int i=0;i<t;i++){
        int n = entrada[i];
        ull ans = 1;
        int j=-1;
        for(pair<int, ull> p:productos){
            if(p.first >= n){
                break;
            }
            j++;
        }
        if(j>-1) ans *= productos[primos[j]];
        j++;
        for(;j<primos.size();j++){
            if(primos[j]<=n){
                ans *= primos[j];
                ans %= 10000000000;
                productos[primos[j]] = ans;
            }else{
                break;
            }
        }
        cout << ans << "\n";
    }
    /*cout << endl;
    for(pair<int, ull> p:productos) cout << p.first << " " << p.second << endl;*/
    return 0;
}
