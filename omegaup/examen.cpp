#include <stdio.h>

using namespace std;

int main()
{
    int e;
    scanf("%d", &e);
    double suma = 0;
    int alumnos = 0;
    for(int i=1;i<=e-1;i++){
        double actual;
        scanf("%lf", &actual);
        if(actual>=6){
            suma += actual;
            alumnos++;
        }
    }
    double promedio;
    scanf("%lf", &promedio);
    double calificacion = promedio*(alumnos+1)-suma;
    printf("%0.2f", calificacion);
    return 0;
}
