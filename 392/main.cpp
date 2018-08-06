#include <bits/stdc++.h>

using namespace std;

int main()
{
    string linea;
    int n;
    while(getline(cin, linea)){
        stringstream ss(linea);
        vector<int> coeficientes;
        while(ss >> n) coeficientes.push_back(n);

        bool primero = true;
        stringstream exp;
        for(int i=0;i<coeficientes.size();i++){
            int coef = coeficientes[i];
            int pot = coeficientes.size() - i - 1;
            if(coef>0){
                if(primero){
                    primero = false;
                }else{
                    exp << " + ";
                }
            }else if(coef<0){
                if(primero){
                    exp << "-";
                    primero = false;
                }else{
                    exp << " - ";
                }
            }
            if(coef!=1 && coef!=-1 && coef!=0){
                if(coef>1) exp << coef;
                else exp << -coef;
            }else{
                if(pot==0){
                    if(coef>0) exp << coef;
                    else if(coef<0) exp << -coef;
                }
            }
            if(coef!=0){
                if(pot==1){
                    exp << "x";
                }
                else if(pot>1){
                    exp << "x^" << pot;
                }
            }
        }
        linea = exp.str();
        if(linea.size()==0) cout << "0\n";
        else cout << linea <<  "\n";

    }
    return 0;
}
