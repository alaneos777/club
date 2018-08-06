#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int llu;

int main()
{
    int n;
    scanf("%d", &n);
    vector<llu> numeros(n);
    for(int i=0;i<n;i++){
        scanf("%llu", &numeros[i]);
    }
    llu primero = numeros[0];
    sort(numeros.begin(), numeros.end());
    int izq=0;
    int der=n-1;
    int piv;
    while(izq<=der){
        piv=(izq+der)/2;
        if(numeros[piv]==primero) break;
        else if(primero<numeros[piv]) der=piv-1;
        else izq=piv+1;
    }
    printf("%d", piv);
    return 0;
}
