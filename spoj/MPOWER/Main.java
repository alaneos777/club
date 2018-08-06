import java.util.*;
import java.math.*;

public class Main{
	public static BigInteger exp_bin_mod(BigInteger x, BigInteger y, BigInteger m){
		BigInteger ans = BigInteger.ONE;
		BigInteger two = BigInteger.valueOf(2);
		while(y.compareTo(BigInteger.ZERO) == 1){
			if(y.mod(two).compareTo(BigInteger.ONE) == 0){
				ans = ans.multiply(x).mod(m);
			}
			y = y.divide(two);
			x = x.multiply(x).mod(m);
		}
		return ans;
	}

	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		BigInteger x, y, m;
		for(int i = 0; i < t; i++){
			x = sc.nextBigInteger();
			y = sc.nextBigInteger();
			m = sc.nextBigInteger();
			System.out.println(exp_bin_mod(x, y, m));
		}
	}
}