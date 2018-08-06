import java.util.*;
import java.math.*;

public class Main{
	public static BigInteger k;

	public static void mult(BigInteger a[], BigInteger b[]){
		BigInteger c[] = new BigInteger[3];
		c[0] = a[0].multiply(b[0]);
		c[1] = a[0].multiply(b[1]).add(a[1].multiply(b[0]));
		c[2] = a[1].multiply(b[1]);
		a[1] = c[1].add(c[2].multiply(k.subtract(BigInteger.ONE)));
		a[0] = c[0].add(c[2].multiply(k.subtract(BigInteger.ONE)));
	}

	public static void polPow(BigInteger a[], int n){
		BigInteger ans[] = {BigInteger.ONE, BigInteger.ZERO};
		BigInteger acum[] = {a[0], a[1]};
		while(n > 0){
			if((n & 1) == 1) mult(ans, acum);
			n >>= 1;
			if(n > 0) mult(acum, acum);
		}
		a[1] = ans[1];
		a[0] = ans[0];
	}


	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		k = sc.nextBigInteger();
		BigInteger p[] = {BigInteger.ZERO, BigInteger.ONE};
		polPow(p, n);
		System.out.println(p[0].add(p[1].multiply(k.subtract(BigInteger.ONE))));
	}
}