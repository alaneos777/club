import java.util.*;
import java.math.*;

public class Main{
	public static int digitSum(int n){
		double r = Math.sqrt(n);
		BigDecimal N = BigDecimal.valueOf(n);
		BigDecimal x = BigDecimal.valueOf(r);
		if((int)r * (int)r == n) return 0;
		for(int i = 1; i <= 3; i++){
			x = x.pow(2).add(N).divide(x.multiply(BigDecimal.valueOf(2)), 200, RoundingMode.HALF_UP);
		}
		String num = x.toString();
		int ans = 0;
		for(int i = 0; i < 101; i++){
			if(num.charAt(i) != '.')
			ans += Character.getNumericValue(num.charAt(i));
		}
		return ans;
	}
	public static void main(String [] args){
		int sum = 0;
		for(int i = 1; i <= 100; i++){
			sum += digitSum(i);
		}
		System.out.println(sum);
	}
}