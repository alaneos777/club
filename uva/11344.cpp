#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int n, s, d;
	cin >> n;
	string m;
	vector<int> seven = {1, 3, 2, 6, 4, 5};
	while(n--){
		cin >> m;
		int suma = 0, alternada = 0, suma7 = 0, mult = 1, lastOne, lastTwo, lastThree;
		for(size_t i = 0; i < m.size(); ++i){
			suma += m[i] - '0';
			alternada += (m[i] - '0') * mult;
			mult *= -1;
			suma7 += (m[m.size() - i - 1] - '0') * seven[i % 6];
		}
		lastOne = m.back() - '0';
		if(m.size() >= 2){
			lastTwo = 10 * (m[m.size() - 2] - '0') + lastOne;
		}else{
			lastTwo = lastOne;
		}
		if(m.size() >= 3){
			lastThree = 100 * (m[m.size() - 3] - '0') + lastTwo;
		}else{
			lastThree = lastTwo;
		}
		bool test = true;
		cin >> s;
		for(int i = 1; i <= s; i++){
			cin >> d;
			switch(d){
				case 2:{
					test = test && (lastOne % 2 == 0);
					break;
				}
				case 3:{
					test = test && (suma % 3 == 0);
					break;
				}
				case 4:{
					test = test && (lastTwo % 4 == 0);
					break;
				}
				case 5:{
					test = test && (lastOne == 0 || lastOne == 5);
					break;
				}
				case 6:{
					test = test && (lastOne % 2 == 0) && (suma % 3 == 0);
					break;
				}
				case 7:{
					test = test && (suma7 % 7 == 0);
					break;
				}
				case 8:{
					test = test && (lastThree % 8 == 0);
					break;
				}
				case 9:{
					test = test && (suma % 9 == 0);
					break;
				}
				case 10:{
					test = test && (lastOne == 0);
					break;
				}
				case 11:{
					test = test && (alternada % 11 == 0);
					break;
				}
				case 12:{
					test = test && (suma % 3 == 0) && (lastTwo % 4 == 0);
					break;
				}
			}
		}
		cout << m << " - ";
		if(test){
			cout << "Wonderful.";
		}else{
			cout << "Simple.";
		}
		cout << "\n";
	}
	return 0;
}