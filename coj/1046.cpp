#include <iostream>

using namespace std;

typedef long long int ull;

int main()
{
    ios_base::sync_with_stdio(0);
    int n;
    ull a, b;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a >> b;
        ull ans = ((b*(b+1)*(b+2)*(b+3)-(a-1)*a*(a+1)*(a+2))/4)%100;
        cout << ans << "\n";
    }
    return 0;
}
