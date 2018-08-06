#include <bits/stdc++.h>

using namespace std;

typedef long long int ull;

struct punto{
    ull x, y;
};

ull area(vector<punto> * puntos, vector<ull> * barrido1, vector<ull> * barrido2, int v, int w){
    ull d1 = (*barrido1)[w] - (*barrido1)[v] + (*puntos)[w].x * (*puntos)[v].y;
    ull d2 = (*barrido2)[w] - (*barrido2)[v] + (*puntos)[v].x * (*puntos)[w].y;
    return abs(d1-d2);
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n;
    while(cin >> n){
        vector<punto> puntos(n);
        for(int i=0;i<n;i++) cin >> puntos[i].x >> puntos[i].y;
        vector<ull> barrido1(n+1, 0);
        vector<ull> barrido2(n+1, 0);
        for(int i=0;i<n;i++){
            barrido1[i+1] += barrido1[i] + puntos[i].x * puntos[(i+1)%n].y;
            barrido2[i+1] += barrido2[i] + puntos[(i+1)%n].x * puntos[i].y;
        }
        bool primero = true;
        int indice = 0;
        ull maximo = 0, area_total = abs(barrido1[n] - barrido2[n]), a=0;
        for(int i=0;i<=n-3;i++){
            int first = i+2;
            int last = n-1;
            if(i==0) last--;
            a = area(&puntos, &barrido1, &barrido2, i, last);
            if(primero){
                primero = false;
                maximo = a;
                indice = i;
            }else{
                if(a > maximo){
                    maximo = a;
                    indice = i;
                }
            }
        }
        ull a1, a2, minimo = 0;
        primero = true;
        cout << "indice=" << indice << endl;
        for(int i=0;i<=n-4;i++){
            int v = indice, w = (indice + 2 + i)%n;
            if(w > v) swap(v, w);
            a = area(&puntos, &barrido1, &barrido2, v, w);
            ull dif = abs(area_total - 2*a);
            if(primero){
                primero = false;
                minimo = dif;
                a1 = a;
                a2 = area_total - a;
            }else{
                if(dif < minimo){
                    minimo = dif;
                    a1 = a;
                    a2 = area_total - a;
                }
            }
        }
        if(a2 > a1) swap(a1, a2);
        cout << a1 << " " << a2 << "\n";
    }
    return 0;
}
