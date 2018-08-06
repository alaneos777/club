#include <bits/stdc++.h>

using namespace std;
typedef long long int ull;

vector<ull> ecuacion(vector<ull> raices){
    vector<ull> coeficientes(raices.size()+1, 0);
    coeficientes[0] = 1;
    for(ull raiz:raices){
        vector<ull> tmp;
        for(ull coeficiente:coeficientes){
            tmp.push_back(-raiz*coeficiente);
        }
        for(int i=0;i<tmp.size();i++){
            coeficientes[i+1] += tmp[i];
        }
    }
    return coeficientes;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n;
    while(cin >> n){
        vector<ull> caso(n);
        for(int i=0;i<n;i++) cin >> caso[i];
        vector<ull> ans = ecuacion(caso);
        bool primero = true;
        stringstream exp;
        for(int i=0;i<ans.size();i++){
            ull coef = ans[i];
            int pot = ans.size() - i - 1;
            if(coef>0){
                if(primero){
                    primero = false;
                }else{
                    exp << "+ ";
                }
            }else if(coef<0){
                exp << "- ";
                primero = false;
            }
            if(coef!=1 && coef!=-1 && coef!=0){
                if(coef>1) exp << coef;
                else exp << -coef;
            }else{
                if(pot==0){
                    if(coef>0) exp << coef;
                    else if(coef<0) exp << -coef;
                    else exp << "+ 0";
                }
            }
            if(coef!=0){
                if(pot==1){
                    exp << "x ";
                }
                else if(pot>1){
                    exp << "x^" << pot << " ";
                }
            }
        }
        cout << exp.str() <<  " = 0\n";
    }
    return 0;
}
