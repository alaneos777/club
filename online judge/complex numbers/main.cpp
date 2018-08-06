#include <bits/stdc++.h>

using namespace std;

bool comparador(pair<double, double>a, pair<double, double> b){
    return a.first > b.first;
}

int main()
{
    const double PI = 3.141592653589793238462643383279502884;
    ios_base::sync_with_stdio(false);
    string linea;
    int contador = 1;
    while(getline(cin, linea)){
        stringstream ss(linea);
        string number;
        int root;
        ss >> number >> root;
        if(number[0] != '-'){
            number = "+" + number;
        }
        string n[2];
        int p = -1;
        for(int i=0;i<number.size();i++){
            if(number[i]=='+' || number[i]=='-') p++;
            if(number[i]!='i') n[p] += number[i];
        }
        int a, b;
        a = atoi(n[0].c_str());
        b = atoi(n[1].c_str());
        double r = sqrt(a*a + b*b);
        double theta = acos(a / r);
        if(b != 0) theta = theta*(b/abs(b));
        r = pow(r, 1/(double)root);
        theta = theta / root;
        vector< pair<double, double> > raices;
        for(int i=0;i<root;i++){
            pair<double, double> actual = {r*cos(theta+2*PI*i/root), r*sin(theta+2*PI*i/root)};
            raices.push_back(actual);
        }
        sort(raices.begin(), raices.end(), comparador);
        cout << "Case " << contador << ":\n";
        for(pair<double, double> a:raices){
            string sgn;
            if(a.second >= 0) sgn = "+";
            cout << fixed << setprecision(3) << a.first << sgn << a.second << "i\n";
        }
        cout << "\n";
        contador++;
    }
    return 0;
}
