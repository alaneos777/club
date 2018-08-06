import java.math.BigInteger;
import java.util.Scanner;

public class Main{
	public static void contar(int n, int frecuencias[]){
		BigInteger ans = BigInteger.ONE;
		for(int i = 1; i <= n; i++){
			ans = ans.multiply(BigInteger.valueOf(i));
		}
		String cad = ans.toString();
		for(int i = 0; i < cad.length(); i++){
			frecuencias[cad.charAt(i) - '0']++;
		}
	}

	public static void main(String [] args){
		int n;
		Scanner s = new Scanner(System.in);
		while(s.hasNextInt()){
			n = s.nextInt();
			if(n == 0) break;
			int frecuencias[] = new int[10];
			contar(n, frecuencias);
			System.out.println(n + "! --");
			for(int i = 0; i <= 4; ++i){
				System.out.print("   (" + i + ")" + String.format("%4d", frecuencias[i]));
			}
			System.out.println("");
			for(int i = 5; i <= 9; ++i){
				System.out.print("   (" + i + ")" + String.format("%4d", frecuencias[i]));
			}
			System.out.println("");
		}
	}
}