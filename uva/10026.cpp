#include <bits/stdc++.h>
using namespace std;

struct trabajo
{
	int id, tiempo, multa;
};

bool comparador(const trabajo & t1, const trabajo & t2){
	return t1.multa * t2.tiempo > t2.multa * t1.tiempo;
}

int main(){
	int casos;
	cin >> casos;
	for(int i = 1; i <= casos; i++){
		int N;
		cin >> N;
		vector<trabajo> trabajos(N);
		for(int j = 0; j < N; j++){
			cin >> trabajos[j].tiempo >> trabajos[j].multa;
			trabajos[j].id = j + 1;
		}
		stable_sort(trabajos.begin(), trabajos.end(), comparador);
		for(int j = 0; j < N; j++){
			cout << trabajos[j].id;
			if(j != N - 1) cout << " ";
		}
		cout << "\n";
		if(i != casos){
			cout << "\n";
		}
	}
	return 0;
}