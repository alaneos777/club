import java.util.*;
import java.math.*;

public class Main{
	public static void main(String [] args){
		BigInteger [] F = new BigInteger[1501];
		F[0] = BigInteger.ZERO;
		F[1] = BigInteger.ONE;
		for(int i = 2; i <= 1500; i++){
			F[i] = F[i - 1].add(F[i - 2]);
		}
		BigInteger [] acum = new BigInteger[1501];
		BigInteger sum = BigInteger.ZERO;
		for(int i = 0; i <= 1500; i++){
			sum = sum.add(F[i]);
			acum[i] = sum;
		}
		BigInteger two = new BigInteger("2");
		int n, caso = 1;
		Scanner sc = new Scanner(System.in);
		while(sc.hasNextInt()){
			n = sc.nextInt();
			if(n == 0) break;
			BigInteger ans = acum[n - 1].add(F[n].divide(two));
			if(F[n].mod(two).intValue() == 0) ans = ans.subtract(BigInteger.ONE);
			System.out.println("Set " + (caso++) + ":\n" + ans);
		}
	}
}