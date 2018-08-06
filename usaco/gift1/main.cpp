/*
ID: alan-en1
LANG: C++
TASK: gift1
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    FILE *fin = fopen("gift1.in", "r");
    FILE *fout = fopen("gift1.out", "w");
    int np;
    fscanf(fin, "%d", &np);
    map< string, int > personas, inicial;
    string nombres[np];
    for(int i=0;i<np;i++){
        char tmp[15];
        fscanf(fin, "%14s", tmp);
        string persona = tmp;
        personas[persona] = 0;
        inicial[persona] = 0;
        nombres[i] = persona;
    }
    for(int i=0;i<np;i++){
        char tmp[15];
        fscanf(fin, "%s", tmp);
        string dador = tmp;
        int dinero, numero_personas;
        fscanf(fin, "%d %d", &dinero, &numero_personas);
        personas[dador] += dinero;
        inicial[dador] = dinero;
        for(int j=0;j<numero_personas;j++){
            char tmp[15];
            fscanf(fin, "%s", tmp);
            string persona_actual = tmp;
            personas[persona_actual] += dinero/numero_personas;
            personas[dador] -= dinero/numero_personas;
        }
    }
    for(int i=0; i<sizeof(nombres)/sizeof(nombres[0]); i++) {
        int dif = personas[nombres[i]] - inicial[nombres[i]];
        fprintf(fout, "%s %d\n", nombres[i].c_str(), dif);
    }
    return 0;
}
