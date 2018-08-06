#include <bits/stdc++.h>
using namespace std;

string numero_a_romano(int n){
    int digito, base = 0;
    string ans = "";
    vector< vector<char> > datos = {{'I', 'V'}, {'X', 'L'}, {'C', 'D'}, {'M', '\0'}};
    int miles = n / 1000;
    do{
        string tmp = "";
        digito = n % 10;
        n /= 10;
        if(base < 3){
        	if(0 <= digito && digito <= 3){
	            tmp.append(digito, datos[base][0]);
	        }else if(digito == 4){
	            tmp += datos[base][0];
	            tmp += datos[base][1];
	        }else if(5 <= digito && digito <= 8){
	            tmp += datos[base][1];
	            tmp.append(digito - 5, datos[base][0]);
	        }else if(digito == 9){
	            tmp += datos[base][0];
	            tmp += datos[base + 1][0];
	        }
        }else{
        	tmp.append(miles, 'M');
        	ans = tmp + ans;
        	break;
        }
        ans = tmp + ans;
        base++;
    }while(n != 0);
    return ans;
}

int romano_a_numero(string n){
    int ans = 0;
    char actual, anterior;
    bool f = false;
    map<char, int> datos = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    for(int i = n.size() - 1; i >= 0; i--){
        actual = n[i];
        if(i > 0) anterior = n[i - 1];
        if(actual == 'V' && anterior=='I') ans+=4, f=true;
        else if(actual == 'X' && anterior == 'I') ans += 9, f = true;
        else if(actual == 'L' && anterior == 'X') ans += 40, f = true;
        else if(actual == 'C' && anterior == 'X') ans += 90, f = true;
        else if(actual == 'D' && anterior == 'C') ans += 400, f = true;
        else if(actual == 'M' && anterior == 'C') ans += 900, f = true;
        else{
            if(!f) ans += datos[actual];
            f = false;
        }
    }
    return ans;
}

int main(){
	ifstream in("p089_roman.txt");
	string str;
	int sum = 0;
	while(in >> str){
		cout << str << " -> " << romano_a_numero(str) << " -> " << numero_a_romano(romano_a_numero(str)) << "\n";
		sum += (int)str.size() - (int)numero_a_romano(romano_a_numero(str)).size();
	}
	cout << sum << "\n";
	return 0;
}