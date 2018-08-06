#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b, c, n, i;
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d %d %d", &a, &b, &c);
        if(b*b-4*a*c>=0) printf("SI\n");
        else printf("NO\n");
    }
    return 0;
}
