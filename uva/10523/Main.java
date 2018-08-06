import java.util.*;
import java.math.*;

public class Main{
	public static BigInteger exp_bin(int x, int y){
		BigInteger X = BigInteger.valueOf(x);
		BigInteger ans = BigInteger.ONE;
		while(y > 0){
			if(y % 2 == 1) ans = ans.multiply(X);
			y >>= 1;
			X = X.multiply(X);
		}
		return ans;
	}

	public static BigInteger suma(int n, int a){
		BigInteger N = BigInteger.valueOf(n);
		BigInteger A = BigInteger.valueOf(a);
		if(a == 1){
			return N.multiply(N.add(BigInteger.ONE)).divide(BigInteger.valueOf(2));
		}else{
			return A.multiply(exp_bin(a, n).multiply(N.multiply(A).subtract(N.add(BigInteger.ONE))).add(BigInteger.ONE)).divide(A.subtract(BigInteger.ONE).pow(2));
		}
	}

	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int n, a;
		while(sc.hasNextInt()){
			n = sc.nextInt();
			a = sc.nextInt();
			System.out.println(suma(n, a));
		}
	}
}