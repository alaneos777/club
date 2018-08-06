#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct info{
    int inicial = -1;
    int tamano = 0;
};

map<int, info> tamanos;
int columna = 1;

template<typename tipo>
struct nodo{
    int izq = -1;
    int der = -1;
    tipo valor;
};
template<typename tipo>
struct arbol{
    int pos = -1;
    vector< nodo<tipo> > nodos;
    arbol(int n){
        nodos.resize(n);
    }
    void agregar(int n, int izq, int der, tipo valor){
        nodos[n].izq = izq;
        nodos[n].der = der;
        nodos[n].valor = valor;
    }
    void maximo(int indice, int nivel){
        if(nodos[indice].izq!=-1) maximo(nodos[indice].izq, nivel+1);
        if(tamanos[nivel].inicial==-1){
            tamanos[nivel].inicial = columna;
        }else{
            tamanos[nivel].tamano = columna - tamanos[nivel].inicial;
        }
        columna++;
        if(nodos[indice].der!=-1) maximo(nodos[indice].der, nivel+1);
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    arbol<int> arbol(n);
    for(int i=0;i<n;i++){
        int a, b, c;
        cin >> a >> b >> c;
        if(b==-1) b=0;
        if(c==-1) c=0;
        arbol.agregar(a-1, b-1, c-1, a);
    }
    arbol.maximo(0, 1);
    int tamano_maximo = -1;
    int nivel_minimo = -1;
    for(map<int, info>::iterator it=tamanos.begin(); it!=tamanos.end(); ++it){
        int n_a = it->first;
        int t_a = it->second.tamano+1;
        if(tamano_maximo == -1){
            tamano_maximo = t_a;
            nivel_minimo = n_a;
        }else{
            if(t_a >= tamano_maximo){
                if(t_a == tamano_maximo){
                    if(n_a < nivel_minimo){
                        nivel_minimo = n_a;
                    }
                }else{
                    nivel_minimo = n_a;
                }
                tamano_maximo = t_a;
            }
        }
    }
    cout << nivel_minimo << " " << tamano_maximo;
    return 0;
}
