#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> primos, phi;
vector<bool> es_primo;

lli fast_pow_mod(lli b, lli e, lli m){
    lli ans = 1;
    while(e){
        if(e & 1){
            ans = (ans * b) % m;
        }
        e >>= 1;
        b = (b * b) % m;
    }
    return ans;
}

void criba_phi(lli n){
    for(lli i = 0; i <= n; i++) phi.push_back(i);
    for(size_t i = 0; i < primos.size(); i++){
        lli p = primos[i];
        for(lli j = p; j <= n; j += p){
            phi[j] -= phi[j] / p;
        }
    }
}

lli phi_single(lli n){
    lli resultado = n;
    for(lli p : primos){
    	if(p * p > n) break;
        if(n % p == 0){
	    while(n % p == 0) n /= p;
	    resultado -= resultado/p;
        }
    }
    if(n > 1) resultado -= resultado/n;
    return resultado;
}

lli multiplicativeOrder(lli a, lli n){
    lli phi_n = phi_single(n);
    lli a1;
    lli order = phi_n;
    for(lli p : primos){
        if(p * p > phi_n) break;
        if(phi_n % p == 0){
            while(phi_n % p == 0){
                phi_n /= p, order /= p;
            }
            a1 = fast_pow_mod(a, order, n);
            while(a1 != 1){
                a1 = fast_pow_mod(a1, p, n);
                order *= p;
            }
        }
    }
    if(phi_n > 1){
        order /= phi_n;
        a1 = fast_pow_mod(a, order, n);
        while(a1 != 1){
            a1 = fast_pow_mod(a1, phi_n, n);
            order *= phi_n;
        }
    }
    return order;
}

void criba_primos(lli n){
    es_primo.resize(n + 1, true);
    es_primo[0] = es_primo[1] = false;
    primos.push_back(2);
    for(lli i = 4; i <= n; i += 2){
        es_primo[i] = false;
    }
    for(lli i = 3; i <= n; i += 2){
        if(es_primo[i]){
            primos.push_back(i);
            for(lli j = i * i; j <= n; j += 2 * i){
                es_primo[j] = false;
            }
        }
    }
}

int main(){
	criba_primos(10000);
	//criba_phi(10000000);
	cout << "hola\n";
	lli ans = 0;
	for(lli n = 3; n <= 100000000; n++){
		lli i = n;
		while(i % 2 == 0) i /= 2;
		while(i % 5 == 0) i /= 5;
		lli period = (i == 1 ? 0 : multiplicativeOrder(10, i));
		//cout << n << " : " << period << "\n";
		ans += period;
	}
	cout << ans << "\n";
}