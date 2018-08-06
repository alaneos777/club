import java.util.*;
import java.math.*;

public class Main{
	public static BigInteger k;

	public static void mult(BigInteger a[], BigInteger b[], BigInteger m){
		BigInteger c[] = new BigInteger[3];
		c[0] = a[0].multiply(b[0]);
		c[1] = a[0].multiply(b[1]).add(a[1].multiply(b[0]));
		c[2] = a[1].multiply(b[1]);
		a[1] = c[1].add(c[2].multiply(k.subtract(BigInteger.ONE))).mod(m);
		a[0] = c[0].add(c[2].multiply(k.subtract(BigInteger.ONE))).mod(m);
	}

	public static void polPow(BigInteger a[], BigInteger n, BigInteger m){
		BigInteger ans[] = {BigInteger.ONE, BigInteger.ZERO};
		BigInteger acum[] = {a[0], a[1]};
		while(n.compareTo(BigInteger.ZERO) == 1){
			if(n.testBit(0)) mult(ans, acum, m);
			n = n.shiftRight(1);
			mult(acum, acum, m);
		}
		a[1] = ans[1];
		a[0] = ans[0];
	}


	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t-- > 0){
			BigInteger n = sc.nextBigInteger();
			k = sc.nextBigInteger();
			BigInteger m = sc.nextBigInteger();
			BigInteger p[] = {BigInteger.ZERO, BigInteger.ONE};
			polPow(p, n, m);
			BigInteger ans = p[0].add(p[1].multiply(k.subtract(BigInteger.ONE)));
			if(n.compareTo(BigInteger.ONE) == 0) ans = ans.add(BigInteger.ONE);
			System.out.println(ans.mod(m));
		}
	}
}