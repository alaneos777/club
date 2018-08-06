import java.util.*;
import java.math.*;

public class Main{
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		String s;
		BigInteger ans = new BigInteger("0");
		while(true){
			s = sc.next();
			if(s.equals("0")) break;
			ans = ans.add(new BigInteger(s));
		}
		System.out.println(ans);
	}
}