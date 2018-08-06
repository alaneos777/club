#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    while(true){
        int n;
        cin >> n;
        if(n == 0) break;
        vector<int> edades(101, 0);
        for(int i=1;i<=n;i++){
            int e;
            cin >> e;
            edades[e]++;
        }
        bool flag = false;
        for(int i=1;i<=100;i++){
            for(int j=1;j<=edades[i];j++){
                if(flag){
                    cout << " ";
                }else{
                    flag = true;
                }
                cout << i;
            }
        }
        cout << "\n";
    }
    return 0;
}
