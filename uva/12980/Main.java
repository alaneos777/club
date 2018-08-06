import java.util.*;
import java.math.*;

public class Main{
	public static BigInteger[] gcd(BigInteger a, BigInteger b){
		BigInteger q, r0 = a, r1 = b, ri, s0 = BigInteger.ONE, s1 = BigInteger.ZERO, si, t0 = BigInteger.ZERO, t1 = BigInteger.ONE, ti;
		while(r1.compareTo(BigInteger.ZERO) != 0){
			q = r0.divide(r1);
			ri = r0.mod(r1);
			r0 = r1;
			r1 = ri;
			si = s0.subtract(s1.multiply(q));
			s0 = s1;
			s1 = si;
			ti = t0.subtract(t1.multiply(q));
			t0 = t1;
			t1 = ti;
		}
		return new BigInteger [] {r0, s0, t0};
	}
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int caso = 1;
		while(true){
			int n = sc.nextInt();
			BigInteger r = sc.nextBigInteger(), ki, d = BigInteger.ZERO;
			if(n == 0) break;
			BigInteger [] ans = new BigInteger[n];
			for(int i = 0; i < n; i++){
				ki = sc.nextBigInteger();
				BigInteger[] info = gcd(d, ki);
				BigInteger s = info[1], t = info[2];
				d = info[0];
				for(int j = 0; j < i; j++){
					ans[j] = ans[j].multiply(s);
				}
				ans[i] = t;
			}
			System.out.print("Case #" + caso + ": ");
			if(r.mod(d).compareTo(BigInteger.ZERO) == 0){
				BigInteger q = r.divide(d);
				for(int i = 0; i < n; i++){
					if(i > 0) System.out.print(" ");
					System.out.print(q.multiply(ans[i]));
				}
				System.out.println("");
			}else{
				System.out.println("Stupid keypad!");
			}
			++caso;
		}
	}
}