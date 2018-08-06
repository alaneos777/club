#include <bits/stdc++.h>

using namespace std;

int primos_distintos(int n){
    int ans = 0;
    if(n==1) return ans;
    map<int, int> f;
    int d=2;
    while(d<=sqrt(n)){
        if(n%d==0){
            f[d]++;
            n /= d;
        }else{
            d++;
        }
    }
    f[n]++;
    for(pair<int, int> p:f) ans++;
    return ans;
}

int main()
{
    int n;
    while(true){
        cin >> n;
        if(n == 0) break;
        cout << n << " : " << primos_distintos(n) << "\n";
    }
    return 0;
}
