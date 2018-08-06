import java.util.*;
import java.math.*;

public class Main{
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		BigDecimal ONE = new BigDecimal("1");
		while(sc.hasNextLong()){
			long n = sc.nextLong();
			BigDecimal ans = BigDecimal.valueOf(n);
			ans = ans.subtract(ONE.divide(ans, 25, RoundingMode.DOWN));
			String str = ans.toString();
			System.out.println(str.substring(0, str.length() - 9));
		}
	}
}