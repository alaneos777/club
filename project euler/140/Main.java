import java.util.*;
import java.math.*;

public class Main{
	static BigInteger TWO = BigInteger.valueOf(2);
	public static BigInteger sqrt(BigInteger n)
	{
	    if (n.signum() >= 0)
	    {
	        final int bitLength = n.bitLength();
	        BigInteger root = BigInteger.ONE.shiftLeft(bitLength / 2);

	        while (!isSqrt(n, root))
	        {
	            root = root.add(n.divide(root)).divide(TWO);
	        }
	        return root;
	    }
	    else
	    {
	        throw new ArithmeticException("square root of negative number");
	    }
	}


	private static boolean isSqrt(BigInteger n, BigInteger root)
	{
	    final BigInteger lowerBound = root.pow(2);
	    final BigInteger upperBound = root.add(BigInteger.ONE).pow(2);
	    return lowerBound.compareTo(n) <= 0
	        && n.compareTo(upperBound) < 0;
	}

	public static void main(String [] args){
		BigInteger sum = BigInteger.ZERO;
		int i = 0;
		BigInteger n = BigInteger.ONE;
		BigInteger t = BigInteger.valueOf(20);
		BigInteger diez = BigInteger.valueOf(10);
		BigInteger dif = BigInteger.valueOf(19);
		while(true){
			if(sqrt(t).pow(2).compareTo(t) == 0){
				sum = sum.add(n);
				i++;
				System.out.println(i + ": " + t + " " + n);
				if(i == 30) break;
			}
			dif = dif.add(diez);
			t = t.add(dif);
			n = n.add(BigInteger.ONE);
		}
		System.out.println(sum);
	}
}