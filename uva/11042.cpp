#include <bits/stdc++.h>

using namespace std;

# define M_PI 3.14159265358979323846

int main()
{
    ios_base::sync_with_stdio(0);
    int m, a, b;
    cin >> m;
    for(int i=0;i<m;i++){
        cin >> a >> b;
        double theta = abs(atan2(b, a) * 180 / M_PI);
        //theta*N = 180*k
        if(theta==0 || theta==180){
            cout << "1";
        }else if(theta==45 || theta==135){
            if(abs(a) <= 128){
                cout << "4";
            }else{
                cout << "TOO COMPLICATED";
            }
        }else if(theta==90){
            cout << "2";
        }else{
            cout << "TOO COMPLICATED";
        }
        cout << "\n";
    }
    return 0;
}
