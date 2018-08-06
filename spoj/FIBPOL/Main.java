import java.util.*;
import java.math.*;

public class Main{
	public static BigInteger sqrt(BigInteger n)
	{
	    if (n.signum() >= 0)
	    {
	        final int bitLength = n.bitLength();
	        BigInteger root = BigInteger.ONE.shiftLeft(bitLength / 2);

	        while (!isSqrt(n, root))
	        {
	            root = root.add(n.divide(root)).divide(BigInteger.valueOf(2));
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
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t-- != 0){
			BigInteger A = sc.nextBigInteger();
			BigInteger D = BigInteger.valueOf(5);
			D = D.multiply(A).add(BigInteger.valueOf(2));
			D = D.multiply(A).add(BigInteger.ONE);
			BigInteger raiz = sqrt(D);
			if(raiz.pow(2).compareTo(D) == 0){
				System.out.println("1");
			}else{
				System.out.println("0");
			}
		}
	}
}