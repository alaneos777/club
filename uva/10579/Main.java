import java.util.*;
import java.math.*;

public class Main{
	public static BigInteger[] F;
	public static void main(String [] args){
		F = new BigInteger[5001];
		F[0] = BigInteger.ZERO;
		F[1] = BigInteger.ONE;
		for(int i = 2; i <= 5000; i++){
			F[i] = F[i - 1].add(F[i - 2]);
		}
		int n;
		Scanner sc = new Scanner(System.in);
		while(sc.hasNextInt()){
			n = sc.nextInt();
			System.out.println(F[n]);
		}
	}
}