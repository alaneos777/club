import java.math.*;
import java.util.*;

public class Main{
	public static int exp_bin_mod(int r, int n, int m){
		BigInteger ans = new BigInteger("1");
		BigInteger R = BigInteger.valueOf(r);
		BigInteger M = BigInteger.valueOf(m);
		while(n > 0){
			if(n % 2 == 1){
				ans = ans.multiply(R).mod(M);
			}
			n >>= 1;
			R = R.multiply(R).mod(M);
		}
		return ans.intValue();
	}

	public static boolean [] es_compuesto;
	public static ArrayList<Integer> primos;

	public static void criba(int n){
		es_compuesto = new boolean[n + 1];
		es_compuesto[0] = es_compuesto[1] = true;
		for(int i = 4; i <= n; i += 2){
			es_compuesto[i] = true;
		}
		primos = new ArrayList<Integer>();
		primos.add(2);
		int limit = (int)Math.sqrt(n);
		for(int i = 3; i <= n; i += 2){
			if(!es_compuesto[i]){
				primos.add(i);
				if(i <= limit){
					for(int j = i * i; j <= n; j += 2 * i){
						es_compuesto[j] = true;
					}
				}
			}
		}
	}

	public static boolean es_primo(int n){
		if(n < es_compuesto.length){
			return !es_compuesto[n];
		}else{
			for(int p : primos){
				if(p * p > n) break;
				if(n % p == 0) return false;
			}
			return true;
		}
	}

	public static void main(String [] args){
		criba(31622);
		Scanner sc = new Scanner(System.in);
		int p, a;
		while(true){
			p = sc.nextInt();
			a = sc.nextInt();
			if(p == 0 && a == 0) break;
			if(!es_primo(p) && exp_bin_mod(a, p, p) == a){
				System.out.println("yes");
			}else{
				System.out.println("no");
			}
		}
	}
}