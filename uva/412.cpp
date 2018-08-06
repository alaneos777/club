#include <bits/stdc++.h>

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int N;
	while(true){
		cin >> N;
		if(N == 0) break;
		vector<int> datos(N);
		int coprimos = 0, total = 0;
		for(int i = 0; i < N; i++)
			cin >> datos[i];
		for(int i = 0; i < N; i++){
			for(int j = i + 1; j < N; j++){
				if(__gcd(datos[i], datos[j]) == 1)
					coprimos++;
				total++;
			}
		}
		if(coprimos == 0)
			cout << "No estimate for this data set.";
		else
			cout << fixed << setprecision(6) << sqrt((double)total * 6 / (double)coprimos);
		cout << "\n";
	}
	return 0;
}