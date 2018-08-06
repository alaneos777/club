#include <iostream>
#include <vector>

using namespace std;

vector<int> divisores;

void criba_divisores(int n){
    divisores.resize(n+1, 0);
    for(int i=1;i<=n;i++){
        for(int j=2*i;j<=n;j+=i){
            divisores[j] += i;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int t;
    int maximo = 1;
    cin >> t;
    vector<int> casos(t);
    for(int i=0;i<t;i++){
        cin >> casos[i];
        if(casos[i] > maximo) maximo = casos[i];
    }
    criba_divisores(maximo);
    for(int i=0;i<t;i++){
        cout << divisores[casos[i]] << "\n";
    }
    return 0;
}
