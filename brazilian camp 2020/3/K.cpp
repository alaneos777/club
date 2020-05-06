#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
using namespace std;
 
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;
 
const int LIM = 1e5;
 
const int ABAJO_IZQ = 0;
const int ABAJO_DER = 1;
const int ARRIBA_IZQ = 2;
const int ARRIBA_DER = 3;
 
int total_comandos;
int n, m;
 
char num_to_letra(int num){
    return (char)('a' + num - 1);
}
 
void agrega(int f1, int c1, int f2, int c2, int f3, int c3){
    cout << num_to_letra(c1) << f1 << " > ";
    cout << num_to_letra(c2) << f2 << " ? ";
    cout << num_to_letra(c3) << f3 << endl;
 
    total_comandos++;
    assert(total_comandos <= LIM);
}
 
void cuadrado_mayor_arriba_izq(int fila, int columna){
    agrega(fila + 1, columna, fila, columna, fila, columna);     
    agrega(fila + 1, columna + 1, fila, columna, fila, columna);
    agrega(fila, columna + 1, fila, columna, fila, columna);
}
void cuadrado_mayor_arriba_der(int fila, int columna){
    agrega(fila, columna, fila, columna + 1, fila, columna);     
    agrega(fila + 1, columna, fila, columna + 1, fila, columna);
    agrega(fila + 1, columna + 1, fila, columna + 1, fila, columna);
}
void cuadrado_mayor_abajo_izq(int fila, int columna){
    agrega(fila + 1, columna + 1, fila + 1, columna, fila, columna);     
    agrega(fila, columna + 1, fila + 1, columna, fila, columna);
    agrega(fila, columna, fila + 1, columna, fila, columna);
}
void cuadrado_mayor_abajo_der(int fila, int columna){
    agrega(fila, columna + 1, fila + 1, columna + 1, fila, columna);     
    agrega(fila, columna, fila + 1, columna + 1, fila, columna);
    agrega(fila + 1, columna, fila + 1, columna + 1, fila, columna);
}
 
// esquina sup izq del cuadro es (fila, columna), dir es a donde quiero poner el mayor
void cuadrado_mayor(int fila, int columna, int dir){
    if(dir == ARRIBA_IZQ) cuadrado_mayor_arriba_izq(fila, columna);
    if(dir == ARRIBA_DER) cuadrado_mayor_arriba_der(fila, columna);
    if(dir == ABAJO_IZQ) cuadrado_mayor_abajo_izq(fila, columna);
    if(dir == ABAJO_DER) cuadrado_mayor_abajo_der(fila, columna);
}
 
// mueve el mayor de los disponibles a (fila, columna), quiza sobreescribiendo los de esta fila
void mueve_mayor(int fila, int columna, bool sobreescribir_fila=false){
    for(int i = 1; i < fila - 1; i++){
        for(int j = 1; j < columna; j++){
            cuadrado_mayor(i, j, ABAJO_DER);
        }
        for(int j = m - 1; j >= columna; j--){
            cuadrado_mayor(i, j, ABAJO_IZQ);
        }
    }
 
    for(int j = 1; j < columna; j++){
        cuadrado_mayor(fila - 1, j, ABAJO_DER);
    }
 
    if(sobreescribir_fila){
        for(int j = m - 1; j >= columna; j--){
            cuadrado_mayor(fila - 1, j, ABAJO_IZQ);
        }
    }
}
 
void resuelve(int fila){
    for(int col = m; col >= 2; col--){
        mueve_mayor(fila, col);
    }
    cuadrado_mayor(fila - 1, 1, ABAJO_IZQ);
    mueve_mayor(fila - 1, 2, true);
 
    agrega(fila, 2, fila - 1, 2, fila - 1, 1); // si el posible mx3 es mayor que el candidato, rota
    cuadrado_mayor(fila - 2, 1, ARRIBA_IZQ); // mueve mx3 a la esquina sup izq
    cuadrado_mayor(fila - 1, 1, ABAJO_IZQ); // mueve mx2 a la esq inf izq
    agrega(fila - 2, 1, fila - 1, 1, fila - 2, 1); // si mx3 es mayor que el que esta debajo, rota
    agrega(fila, 1, fila, 2, fila - 1, 1); // acomoda el ultimo
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    cin >> n;
    m = n;
 
    if(n == 2){
        agrega(2, 1, 2, 2, 1, 1);
        return 0;
    }
 
    for(int fila = n; fila >= 3; fila--){
        resuelve(fila);
    }
 
    return 0;
}
