import java.util.*;
import java.math.*;

public class Main{
	public static BigInteger diez = BigInteger.valueOf(10);

	public static BigInteger reverseDigits(BigInteger n){
		BigInteger ans = BigInteger.ZERO;
		while(n.compareTo(BigInteger.ZERO) == 1){
			BigInteger digit = n.mod(diez);
			ans = ans.multiply(diez).add(digit);
			n = n.divide(diez);
		}
		return ans;
	}

	public static boolean lychrel(int n){
		int steps = 0;
		BigInteger i = BigInteger.valueOf(n);
		while(true){
			i = i.add(reverseDigits(i));
			steps++;
			if(i.compareTo(reverseDigits(i)) == 0) return false;
			if(steps == 50) return true;
		}
	}

	public static void main(String [] args){
		int ans = 0;
		for(int i = 1; i < 10000; i++){
			if(lychrel(i)){
				System.out.println(i);
				ans++;
			}
		}
		System.out.println("\n" + ans);
	}
}