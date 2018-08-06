#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    int t, n, m, v;
    cin >> t;
    for(int i=0;i<t;i++){
        cin >> n >> m;
        vector<int> votos_candidatos(n, 0);
        for(int j=0;j<m;j++){
            for(int k=0;k<n;k++){
                cin >> v;
                votos_candidatos[k] += v;
            }
        }
        int ganador = 0, maximo = votos_candidatos[0];
        for(int j=1;j<n;j++){
            if(votos_candidatos[j] > maximo){
                maximo = votos_candidatos[j];
                ganador = j;
            }
        }
        cout << (ganador+1) << "\n";
    }
    return 0;
}
