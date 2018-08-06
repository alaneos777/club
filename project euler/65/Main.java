import java.util.*;
import java.math.*;

public class Main{
	public static void main(String [] args){
		BigInteger num = BigInteger.ZERO;
		BigInteger den = BigInteger.ONE;
		for(int i = 99; i >= 0; i--){
			BigInteger ai;
			if(i == 0){
				ai = BigInteger.valueOf(2);
			}else{
				if(i % 3 == 2){
					ai = BigInteger.valueOf(2 * (i + 1) / 3);
				}else{
					ai = BigInteger.ONE;
				}
			}
			BigInteger tmp = den;
			den = ai.multiply(den).add(num);
			num = tmp;
		}
		System.out.println(den + " / " + num);
		BigInteger diez = BigInteger.valueOf(10);
		BigInteger sum = BigInteger.ZERO;
		while(den.compareTo(BigInteger.ZERO) == 1){
			sum = sum.add(den.mod(diez));
			den = den.divide(diez);
		}
		System.out.println(sum);
	}
}