import java.math.BigInteger;
import java.util.Scanner;

public class Main{
	public static int factorial_suma(int n){
		BigInteger ans = BigInteger.ONE;
		for(int i = 1; i <= n; i++){
			ans = ans.multiply(BigInteger.valueOf(i));
		}
		String cad = ans.toString();
		int suma = 0;
		for(int i = 0; i < cad.length(); i++){
			suma += (cad.charAt(i) - '0');
		}
		return suma;
	}

	public static void main(String [] args){
		int n;
		Scanner s = new Scanner(System.in);
		while(s.hasNextInt()){
			n = s.nextInt();
			System.out.println(factorial_suma(n));
		}
	}
}