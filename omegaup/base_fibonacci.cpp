#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

long long int f(int n){
    long double phi1 = (1+sqrt(5))/2;
    long double phi2 = (1-sqrt(5))/2;
    return floor((pow(phi1, n+1) - pow(phi2, n+1))/sqrt(5));
}

int posicion_cercana(long long int F_n){
    F_n+=2;
    long double phi = (1+sqrt(5))/2;
    return floor(log((sqrt(5)*F_n+sqrt(5*F_n*F_n+4))/2)/log(phi));
}

vector<int> digitos;

void base_f(long long int n){
    int i = posicion_cercana(n);
    while(f(i) > n) i--;
    digitos.push_back(i);
    n -= f(i);
    if(n!=0) base_f(n);
}

int main()
{
    long long int n;
    cin >> n;
    base_f(n);
    int tamano = digitos.size();
    cout << tamano << endl;
    for(int i=0;i<tamano;i++){
        cout << digitos[i] << " ";
    }
    return 0;
}
