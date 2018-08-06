#include <bits/stdc++.h>

using namespace std;

void imprimir(int n){
    if(0 <= n && n<=9) cout << "  " << n;
    else if(10 <= n && n<=99) cout << " " << n;
    else cout << n;
}

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

int fast_pow(int b, int e){
    int ans = 1;
    while(e > 0){
        if(e%2 == 1){
            ans *= b;
        }
        e = e >> 1;
        b *= b;
    }
    return ans;
}

map<int, int> factorizar_factorial(int n){
    map<int, int> f;
    for(int i=0;i<primos.size();i++){
        int d = primos[i];
        if(d>n) break;
        int contador = 0;
        int j = 1;
        while(true){
            int tmp = n/fast_pow(d, j);
            contador += tmp;
            if(tmp == 0) break;
            j++;
        }
        f[d] += contador;
    }
    return f;
}

int main()
{
    ios_base::sync_with_stdio(0);
    vector<int> casos;
    int maximo = 0;
    while(true){
        int n;
        cin >> n;
        if(n==0) break;
        casos.push_back(n);
        if(n > maximo) maximo = n;
    }
    criba(maximo);
    for(int n:casos){
        map<int, int> f=factorizar_factorial(n);
        imprimir(n);
        cout << "! =";
        int c = 0;
        for(pair<int, int>i:f){
            if(c==15) cout << endl << "      ";
            imprimir(i.second);
            c++;
        }
        cout << "\n";
    }
    return 0;
}
