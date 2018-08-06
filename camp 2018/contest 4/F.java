import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.math.BigInteger;

class Main {
  static class Scanner{
    InputStreamReader isr = new InputStreamReader(System.in);
    BufferedReader br = new BufferedReader(isr);
    StringTokenizer st = new StringTokenizer("");
    int espacios = 0;

    public String nextLine() throws IOException{
      if(espacios>0){
        espacios--;
        return "";
      }else if(st.hasMoreTokens()){
        StringBuilder salida = new StringBuilder();
        while(st.hasMoreTokens()){
          salida.append(st.nextToken());
          if(st.countTokens()>0){
            salida.append(" ");
          }
        }
        return salida.toString();
      }
      return br.readLine();
    }

    public String next() throws IOException{
      espacios=0;
      while (!st.hasMoreTokens() ) {
        st = new StringTokenizer(br.readLine() );
      }
      return st.nextToken();
    }

    public boolean hasNext() throws IOException{
      while (!st.hasMoreTokens()) {
        String linea = br.readLine();
        if (linea == null) {
          return false;
        }
        if(linea.equals("")){
          espacios++;
        }
        st = new StringTokenizer(linea);
      }
      return true;
    }
  }
  
  public static void main (String[] args) throws java.lang.Exception
	{
		int a,b;
		String num;
		Scanner sc = new Scanner();
		a = Integer.parseInt(sc.next());
		num = sc.next();
		b = Integer.parseInt(sc.next());

		BigInteger A = new BigInteger(num, a);
		System.out.println(A.toString(b));
	}
}
