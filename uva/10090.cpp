#include <bits/stdc++.h>

using namespace std;
typedef long long int ull;

vector<ull> euclides(ull a, ull b){
    ull x0 = 1, y0 = 0, x1 = 0, y1 = 1, xn, yn, q, r;
    while(b != 0){
        q = a/b, r = a%b;
        xn = x0 - x1*q, yn = y0 - y1*q;
        x0 = x1, x1 = xn;
        y0 = y1, y1 = yn;
        a = b, b = r;
    }
    return {a, x0, y0};
}

int main()
{
    ios_base::sync_with_stdio(0);
    ull n, c1, n1, c2, n2, x, y, d, q, m1, m2;
    while(true){
        cin >> n;
        if(n==0) break;
        cin >> c1 >> n1 >> c2 >> n2;
        //tipo 1: costo c1, n1 objetos
        //tipo 2: costo c1, n2 objetos
        //n=n1m1+n2m2
        //c=c1m1+c2m2
        vector<ull> sol = euclides(n1, n2);
        d = sol[0], x = sol[1], y = sol[2];
        m1 = m2 = -1;
        if(n%d == 0){
            q = n/d;
            //m1=xq-(n2/d)k, m2=yq+(n1/d)k
            //-yqd/n1 < k< xqd/n2
            double lower = -(double)(y*q)/(double)(n1/d), upper = (double)(x*q)/(double)(n2/d);
            ull a = ceil(min(lower, upper)), b = floor(max(lower, upper));
            if(a<=b){
                //c=q(c1x+c2y)+k(c2n1-c1n2)/d
                ull tmp = c2*(n1/d)-c1*(n2/d);
                if(tmp >= 0){
                    m1 = x*q-(n2/d)*a, m2 = y*q+(n1/d)*a;
                }else{
                    m1 = x*q-(n2/d)*b, m2 = y*q+(n1/d)*b;
                }
            }
        }
        if(m1!=-1 && m2!=-1){
            cout << m1 << " " << m2 << "\n";
        }else{
            cout << "failed\n";
        }
    }
    return 0;
}
