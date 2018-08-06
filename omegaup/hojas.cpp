#include <iostream>
#include <vector>

using namespace std;

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
    void agregar(tipo valor, int donde){
        if(pos == -1){
            pos++;
            nodos[pos].valor = valor;
        }else{
            if(valor < nodos[donde].valor){
                if(nodos[donde].izq==-1){
                    pos++;
                    nodos[donde].izq = pos;
                    nodos[pos].valor = valor;
                }else{
                    agregar(valor, nodos[donde].izq);
                }
            }else{
                if(nodos[donde].der==-1){
                    pos++;
                    nodos[donde].der = pos;
                    nodos[pos].valor = valor;
                }else{
                    agregar(valor, nodos[donde].der);
                }
            }
        }
    }
    void agregar(int n, int izq, int der, tipo valor){
        nodos[n].izq = izq;
        nodos[n].der = der;
        nodos[n].valor = valor;
    }
    void pre_order(int indice){
        cout << nodos[indice].valor << " ";
        if(nodos[indice].izq!=-1) pre_order(nodos[indice].izq);
        if(nodos[indice].der!=-1) pre_order(nodos[indice].der);
    }
    void in_order(int indice){
        if(nodos[indice].izq!=-1) in_order(nodos[indice].izq);
        cout << nodos[indice].valor << " ";
        if(nodos[indice].der!=-1) in_order(nodos[indice].der);
    }
    void post_order(int indice){
        if(nodos[indice].izq!=-1) post_order(nodos[indice].izq);
        if(nodos[indice].der!=-1) post_order(nodos[indice].der);
        cout << nodos[indice].valor << " ";
    }
};

int main()
{
    int n;
    cin >> n;
    int numeros[n];
    for(int i=0;i<n;i++) cin >> numeros[i];
    arbol<int> arbol(n);
    for(int i=n-1;i>=0;i--) arbol.agregar(numeros[i], 0);
    arbol.pre_order(0);
    return 0;
}
