#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    long long int m, n, pedidos;
    cin >> m >> n >> pedidos;
    for(int i=1;i<=pedidos;i++){
        long long int p;
        cin >> p;
        //cout << ( ceil((double)p/(double)m) + n*(m - 1 - ((p - 1) % m) ) ) << " ";
        cout << ( 1 + (p - 1)/m + n*(m - 1 - ((p - 1) % m) ) ) << " ";
    }
    return 0;
}
