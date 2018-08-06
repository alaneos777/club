import java.util.*;
import java.math.*;

public class Main{
	public static boolean form(BigInteger n){
		String s = n.toString();
		if(s.length() != 19) return false;
		for(int i = 1; i <= 10; i++){
			if(Character.getNumericValue(s.charAt(2*i-2)) != (i % 10)) return false;
		}
		return true;
	}
	public static void main(String [] args){
		long i = 1000000000;
		while(true){
			if(form(BigInteger.valueOf(i).pow(2))) break;
			i += 10;
		}
		System.out.println(i);
	}
}