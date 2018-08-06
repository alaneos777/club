import java.util.*;
import java.math.*;

public class Main{
	public static void main(String [] args){
		int n = 204;
		BigInteger [][] pascal = new BigInteger[n + 1][];
		for(int i = 0; i <= n; i++){
			pascal[i] = new BigInteger[i + 1];
			pascal[i][0] = pascal[i][i] = BigInteger.ONE;
			for(int j = 1; j <= (i / 2); j++){
				pascal[i][j] = pascal[i][i - j] = pascal[i - 1][j - 1].add(pascal[i - 1][j]);
			}
		}
		for(int i = 0; i <= n; i++){
			for(int j = 0; j <= i; j++){
				if(j > 0) System.out.print(" ");
				System.out.print(pascal[i][j]);
			}
			System.out.println("");
		}
	}
}