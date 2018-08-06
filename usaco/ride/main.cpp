/*
ID: alan-en1
LANG: C++
TASK: ride
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    FILE *fin = fopen("ride.in", "r");
    FILE *fout = fopen("ride.out", "w");
    rewind(fin);
    char nombre[7], cometa[7];
    fscanf(fin, " %s %s", nombre, cometa);
    int p1, p2, r;
    p1=1;
    p2=1;
    for(int i=0;nombre[i]!=0;i++){
        p1 *= nombre[i] - 64;
    }
    for(int i=0;cometa[i]!=0;i++){
        p2 *= cometa[i] - 64;
    }
    r = p1 - p2;
    if(r%47 == 0){
        fprintf (fout, "GO\n");
    }else{
        fprintf (fout, "STAY\n");
    }
    return 0;
}
