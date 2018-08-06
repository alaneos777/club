#include <bits/stdc++.h>

using namespace std;

vector<int> primos;

void criba(int n){
    vector<bool> tmp(n+1, true);
    tmp[1] = true;
    int bound = sqrt(n);
    for(int i=2;i<=bound;i++){
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
    criba(1000);
    int n, c, maximo = 0;
    while(cin >> n >> c){
        vector<int> subset;
        for(int p:primos){
            if(p<=n) subset.push_back(p);
        }
        int s = subset.size(), a, b;
        cout << n << " " << c << ":";
        if(s%2==1){
            a = max((s+1)/2-c, 0), b = min((s-3)/2+c, s-1);
        }else{
            a = max(s/2-c, 0) , b=min(s/2-1+c, s-1);
        }
        for(int k=a;k<=b;k++) cout << " " << subset[k];
        cout << "\n\n";
    }
    return 0;
}
