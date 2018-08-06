import java.util.*;
import java.math.*;

public class Main{
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int n;
		n = sc.nextInt();
		for(int i = 1; i <= n; i++){
			String str;
			BigDecimal suma = BigDecimal.ZERO;
			while(true){
				str = sc.next();
				if(str.equals("0")){
					System.out.println(suma.stripTrailingZeros().toPlainString());
					break;
				}
				suma = suma.add(new BigDecimal(str));
			}
		}
	}
}