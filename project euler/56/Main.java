import java.util.*;
import java.math.*;

public class Main{
	public static BigInteger diez = BigInteger.valueOf(10);

	public static BigInteger digitSum(BigInteger n){
		BigInteger ans = BigInteger.ZERO;
		while(n.compareTo(BigInteger.ZERO) == 1){
			ans = ans.add(n.mod(diez));
			n = n.divide(diez);
		}
		return ans;
	}

	public static void main(String [] args){
		BigInteger ans = BigInteger.ZERO;
		for(int i = 1; i < 100; i++){
			for(int j = 1; j < 100; j++){
				BigInteger tmp = digitSum(BigInteger.valueOf(i).pow(j));
				if(tmp.compareTo(ans) == 1){
					ans = tmp;
				}
			}
		}
		System.out.println(ans);
	}
}