#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;

int main()
{
    ull n;
    cin >> n;
    ull ans = 0;
    vector<ull> p2 = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728};
    for(ull i=1;i<=n;i++){
        ull tmp=0, j=1;
        while(true){
            tmp = i/p2[j];
            ans += tmp;
            if(tmp == 0) break;
            j++;
        }
        ans += tmp;
    }
    cout << ans;
    return 0;
}
