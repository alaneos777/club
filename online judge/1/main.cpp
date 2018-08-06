#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void mapa(int n, int m, int x, int y){
	char we, ns;
	bool b = false;
	if(x > n){
		we = 'E';
	}else if(x < n){
		we = 'O';
	}else{
		b = true;
	}
	if(y > m){
		ns = 'N';
	}else if(y < m){
		ns = 'S';
	}else{
		b = true;
	}
	if(b){
		printf("divisa\n");
	}else{
		printf("%c%c\n", ns, we);
	}
}

int main(int argc, char** argv) {
	int k;
	int n, m;
	while(true){
		scanf("%d", &k);
		if(k == 0) break;
		scanf("%d %d", &n, &m);
		for(int i=1;i<=k;i++){
			int x, y;
			scanf("%d %d", &x, &y);
			mapa(n, m, x, y);
		}
	}
	return 0;
}
