#include <stdio.h>
#include <list>
#include <vector>

using namespace std;

struct year{
    unsigned long long int n;
    bool pasado;
};

unsigned long long int mcd_single(unsigned long long int a, unsigned long long int b){
    if(b==0) return a;
    else return mcd_single(b, a%b);
}
unsigned long long int mcm_single(unsigned long long int a, unsigned long long int b){
    if(a > b) return b*(a/mcd_single(a, b));
    else return a*(b/mcd_single(a, b));
}
unsigned long long int mcm(list<unsigned long long int> numeros){
    while(numeros.size() > 1){
        unsigned long long int a = numeros.front();
        numeros.pop_front();
        unsigned long long int b = numeros.front();
        numeros.pop_front();
        numeros.push_front(mcm_single(a, b));
    }
    return numeros.front();
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<year> arreglo(n);
    for(int i=0;i<n;i++){
        scanf("%llu", &arreglo[i].n);
        arreglo[i].pasado = false;
    }
    list<unsigned long long int> numeros;
    int indice = 0;
    while(indice < n){
        if(!arreglo[indice].pasado){
            unsigned long long int inicial = arreglo[indice].n;
            arreglo[indice].pasado = true;
            unsigned long long int actual = inicial;
            unsigned long long int suma = 0;
            do{
                arreglo[actual - 1].pasado = true;
                actual = arreglo[actual - 1].n;
                suma++;
            }while(actual!=inicial);
            numeros.push_back(suma);
        }
        indice++;
    }
    numeros.sort();
    numeros.unique();
    printf("%llu", mcm(numeros));
    return 0;
}
