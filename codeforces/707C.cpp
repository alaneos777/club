#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int ull;

int main()
{
    ios_base::sync_with_stdio(0);
    ull n, m, k, bound, tmp, suma, resta;
    cin >> n;
    vector<ull> divisores;
    bound = sqrt(n);
    for(ull i=1;i<=bound;i++){
        if(n%i==0){
            divisores.push_back(i);
        }
    }
    bool encontrada = false;
    //test 1:
    for(ull d:divisores){
        //d <= tmp
        tmp = n/d;
        suma = tmp+d;
        if(suma%2==0 && tmp>d){
            resta = tmp-d;
            m = suma/2, n = resta/2;
            encontrada = true;
            break;
        }
    }
    if(encontrada){
        cout << 2*m*n << " " << m*m+n*n;
    }else{
        //test 2:
        if(n%2==0){
            for(ull d:divisores){
                tmp = n/d;
                if(d%2==0){
                    d /= 2;
                }else{
                    tmp /= 2;
                }
                if(tmp != d){
                    m = max(tmp, d), n = min(tmp, d);
                    encontrada = true;
                    break;
                }
            }
        }
        if(encontrada){
            cout << (m+n)*(m-n) << " " << m*m+n*n;
        }else{
            cout << "-1";
        }
    }
    return 0;
}
