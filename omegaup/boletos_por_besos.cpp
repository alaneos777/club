#include <iostream>
#include <math.h>

using namespace std;

int suma_digitos(int n){
    int ans = 0;
    while(n!=0){
        ans += n%10;
        n /= 10;
    }
    return ans;
}

int n_digitos(int n){
    return ceil(log10(n+1));
}

int main()
{
    int n;
    cin >> n;
    int p = 0;
    while(suma_digitos(n)!=21){
        p++;
        n++;
        n = n%10000000;
    }
    cout << p << " ";
    for(int i=7-n_digitos(n);i>=1;i--){
        cout << 0;
    }
    cout << n;
    return 0;
}
