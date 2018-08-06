#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    cout << "Lumberjacks:\n";
    for(int i=1;i<=n;i++){
        int signo;
        int a, b;
        cin >> a >> b;
        if(a > b) signo = -1;
        else if(a < b) signo = 1;
        else signo = 0;
        bool ordered = true;
        for(int j=1;j<=8;j++){
            int c;
            cin >> c;
            if(!((signo == 1 && b < c) || (signo == -1 && b > c))){
                ordered = false;
            }
            b = c*1;
        }
        if(ordered){
            cout << "Ordered\n";
        }else{
            cout << "Unordered\n";
        }
    }
    return 0;
}
