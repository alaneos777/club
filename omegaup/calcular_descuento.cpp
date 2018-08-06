#include <stdio.h>

using namespace std;

int main()
{
    double n;
    scanf("%lf", &n);
    if(n>1000) printf("%0.2lf", n*0.85);
    else printf("%0.2lf", n);
    return 0;
}
