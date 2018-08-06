#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N, a, b, x;
    cin >> N;
    vector<vector<int>> graph(N + 1, vector<int>());
    for(int i = 1; i <= N - 1; i++){
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    cin >> x;
    vector<bool> visited(N + 1, false);
    
    queue<int> cola;
    cola.push(1);
    int nivel = 1;
    while(!cola.empty()){
        int size = cola.size();
        if(nivel == x){
            cout << size << "\n";
            break;
        }
        while(size--){
            int actual = cola.front();
            cola.pop();
            visited[actual] = true;
            for(int & dest : graph[actual]){
                if(!visited[dest]) cola.push(dest);
            }
        }
        nivel++;
    }
    return 0;
}