import java.util.*;
import java.math.*;

public class Main{
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int n, f, caso = 1;
		while(true){
			n = sc.nextInt();
			f = sc.nextInt();
			if(n == 0 && f == 0) break;
			BigInteger suma = BigInteger.ZERO;
			BigInteger V;
			for(int i = 1; i <= n; i++){
				V = sc.nextBigInteger();
				suma = suma.add(V);
			}
			System.out.println("Bill #" + caso + " costs " + suma + ": each friend should pay " + suma.divide(BigInteger.valueOf(f)) + "\n");
			caso++;
		}
	}
}