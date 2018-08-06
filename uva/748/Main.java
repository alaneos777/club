import java.math.*;
import java.util.Scanner;

public class Main{
	public static BigDecimal exp_bin(BigDecimal r, int n){
		BigDecimal ans = new BigDecimal("1");
		while(n > 0){
			if(n % 2 == 1){
				ans = ans.multiply(r);
			}
			n >>= 1;
			r = r.multiply(r);
		}
		return ans.stripTrailingZeros();
	}

	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		while(sc.hasNextBigDecimal()){
			BigDecimal r = sc.nextBigDecimal();
			int n = sc.nextInt();
			System.out.println(exp_bin(r, n).toPlainString().replaceFirst("^0\\.", "."));
		}
	}
}