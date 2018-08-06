#include <stdio.h>
#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    unordered_map<string, int> nombres;
    char tmp[12];
    for(int i=1;i<=n;i++){
        scanf("%11s", tmp);
        nombres[tmp] = i;
    }
    int tabla[n+1][n+1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d", &tabla[i][j]);
        }
    }
    int p;
    scanf("%d", &p);
    for(int i=1;i<=p;i++){
        scanf("%11s", tmp);
        int pos1 = nombres[tmp];
        scanf("%11s", tmp);
        int pos2 = nombres[tmp];
        if(tabla[pos1][pos2]==1) printf("1\n");
        else printf("0\n");
    }
    return 0;
}
