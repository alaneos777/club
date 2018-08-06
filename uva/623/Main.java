import java.math.BigInteger;
import java.util.Scanner;

public class Main{
	public static BigInteger factorial(int n){
		BigInteger ans = BigInteger.ONE;
		for(int i = 1; i <= n; i++){
			ans = ans.multiply(BigInteger.valueOf(i));
		}
		return ans;
	}

	public static void main(String [] args){
		int n;
		Scanner s = new Scanner(System.in);
		while(s.hasNextInt()){
			n = s.nextInt();
			System.out.println(n + "!");
			System.out.println(factorial(n));
		}
	}
}