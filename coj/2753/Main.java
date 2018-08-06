import java.util.*;
import java.math.*;
import java.io.*;

public class Main{

	public static void main(String [] args){
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		String line = "";
		try{
			while((line = br.readLine()) != null){
				st = new StringTokenizer(line);
				BigInteger n = new BigInteger(st.nextToken());
				BigInteger c = new BigInteger(st.nextToken());
				BigInteger m = new BigInteger(st.nextToken());
				System.out.println(c.modPow(n, m));
			}
		}catch(IOException e){
			//
		}
	}
}