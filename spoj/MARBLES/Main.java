import java.util.*;
import java.math.*;

public class Main{
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t-- != 0){
			int n = sc.nextInt() - 1;
			int k = sc.nextInt() - 1;
			int r = n - k;
			if(r < k){
				int tmp = r;
				r = k;
				k = tmp;
			}
			BigInteger ans = BigInteger.ONE;
			for(int i = r + 1; i <= n; i++){
				ans = ans.multiply(BigInteger.valueOf(i));
			}
			for(int i = 1; i <= k; i++){
				ans = ans.divide(BigInteger.valueOf(i));
			}
			System.out.println(ans);
		}
	}
}