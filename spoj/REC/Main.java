import java.util.*;
import java.math.*;

public class Main{
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t-- != 0){
			BigInteger a = sc.nextBigInteger();
			BigInteger b = sc.nextBigInteger();
			BigInteger n = sc.nextBigInteger();
			BigInteger m = sc.nextBigInteger();
			if(a.compareTo(BigInteger.ZERO) == 0){
				if(n.compareTo(BigInteger.ZERO) == 0){
					System.out.println(BigInteger.ONE.mod(m));
				}else{
					System.out.println(b.mod(m));
				}
			}else if(a.compareTo(BigInteger.ONE) == 0){
				System.out.println(b.mod(m).multiply(n.mod(m)).add(BigInteger.ONE).mod(m));
			}else{
				BigInteger M = m.multiply(a.subtract(BigInteger.ONE));
				System.out.println(b.mod(m).multiply(a.modPow(n, M).subtract(BigInteger.ONE)).mod(M).divide(a.subtract(BigInteger.ONE)).mod(m).add(a.modPow(n, m)).mod(m));
			}
		}
	}
}