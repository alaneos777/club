#include <stdio.h>
#include <math.h>

using namespace std;

unsigned long long int elevar(unsigned long long a, int b){
    if(b==0) return 1;
    else if(b==1) return a;
    else if(b%2==0) return elevar(a*a, b/2);
    else if(b%2==1) return a*elevar(a*a,(b-1)/2);
}

int main()
{
    unsigned long long int n;
    scanf("%llu", &n);
    int nivel = floor(log2(n));
    unsigned long long int ans = n+1-elevar(2,nivel);
    printf("%d %llu", ans%10, ans);
    return 0;
}
