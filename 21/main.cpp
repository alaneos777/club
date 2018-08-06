#include <bits/stdc++.h>

using namespace std;

typedef uint64_t ull;

vector<ull> primos;

void criba(ull n){
    vector<bool> tmp(n+1, true);
    tmp[1] = false;
    for(ull i=2;i*i<=n;i++){
        while(!tmp[i]) i++;
        for(ull j=2*i;j<=n;j+=i){
            tmp[j] = false;
        }
    }
    for(ull i=1;i<=n;i++){
        if(tmp[i]) primos.push_back(i);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ull maximo = 0;
    cin >> n;
    vector< pair<ull, ull> > entrada(n);
    for(int i=0;i<n;i++){
        ull a, b;
        cin >> a >> b;
        if(a > maximo) maximo = a;
        if(b > maximo) maximo = b;
        entrada[i] = make_pair(a, b);
    }
    cout << maximo;
    criba(maximo);

    return 0;
}
