#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    int n;
    cin >> n;
    unordered_map<int, int> botas;
    for(int i=1;i<=n;i++){
        int bota;
        cin >> bota;
        botas[bota]++;
    }
    int ans = 0;
    for(pair<int, int> par : botas){
        if(par.second%2!=0) ans++;
    }
    cout << ans;
    return 0;
}
