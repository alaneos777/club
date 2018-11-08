#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
typedef map<int, int> MAP;
int N, M, V[1000000], R[1000000];
int main() {
scanf("%d%d", &N, &M);
while (N > 0) {
for (int i = 0; i < N; ++i) scanf("%d", &V[i]);
MAP mp;
R[N - 1] = N;
mp[V[N - 1]] = N - 1;
for (int i = N - 2; i >= 0; --i) {
R[i] = R[i + 1];
if (mp.count(V[i])) R[i] = min(R[i], mp[V[i]]);
mp[V[i]] = i;
}
for (int i = 0; i < M; ++i) {
int a, b;
scanf("%d%d", &a, &b);
--a; --b;
if (R[a] <= b) printf("%d\n", V[R[a]]);
else printf("OK\n");
}
printf("\n");
scanf("%d%d", &N, &M);
}
}
