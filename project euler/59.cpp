#include <bits/stdc++.h>
using namespace std;

int main(){
	ifstream in("p059_cipher.txt");
	string message = "", key = "   ";
	int c;
	while(in >> c){
		message.push_back((char)c);
	}
	vector<vector<char>> freq(3, vector<char>(256));
	vector<pair<char, int>> most(3);
	for(int i = 0; i < message.size(); i++){
		freq[i % 3][message[i]]++;
	}
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 256; j++){
			if(freq[i][j] > most[i].second){
				most[i].first = j;
				most[i].second = freq[i][j];
			}
		}
	}
	for(int i = 0; i < 3; i++){
		key[i] = most[i].first ^ ' ';
	}
	cout << "Key: " << key << "\nMessage:\n";
	int sum = 0;
	for(int i = 0; i < message.size(); i++){
		message[i] ^= key[i % 3];
		sum += message[i];
	}
	cout << message << "\nSum = " << sum << "\n";;
	return 0;
}