import java.util.*;
import java.math.*;

public class Main{

	static BigInteger cero = new BigInteger("0");
	static BigInteger uno = new BigInteger("1");

	static BigInteger piso(BigInteger a, BigInteger b){
		if((a.compareTo(cero) >= 0 && b.compareTo(cero) > 0) || (a.compareTo(cero) < 0 && b.compareTo(cero) < 0)){
			return a.divide(b);
		}else{
			if(a.mod(b).compareTo(cero) == 0) return a.divide(b);
			else return a.divide(b).subtract(uno);
		}
	}

	static BigInteger techo(BigInteger a, BigInteger b){
		if((a.compareTo(cero) >= 0 && b.compareTo(cero) > 0) || (a.compareTo(cero) < 0 && b.compareTo(cero) < 0)){
			if(a.mod(b).compareTo(cero) == 0) return a.divide(b);
			else return a.divide(b).add(uno);
		}else{
			return a.divide(b);
		}
	}

	static ArrayList<BigInteger> euclides(BigInteger a, BigInteger b){
		BigInteger r0 = a, r1 = b, ri, s0 = uno, s1 = cero, si, t0 = cero, t1 = uno, ti, q;
		while(r1.compareTo(cero) != 0){
			q = r0.divide(r1);
			ri = r0.mod(r1);
			si = s0.subtract(s1.multiply(q));
			ti = t0.subtract(t1.multiply(q));
			r0 = new BigInteger(r1.toString());
			r1 = new BigInteger(ri.toString());
			s0 = new BigInteger(s1.toString());
			s1 = new BigInteger(si.toString());
			t0 = new BigInteger(t1.toString());
			t1 = new BigInteger(ti.toString());
		}
		ArrayList<BigInteger> info = new ArrayList<BigInteger>();
		info.add(r0);
		info.add(s0);
		info.add(t0);
		return info;
	}

	public static void main(String [] args){
		Scanner entrada = new Scanner(System.in);
		int casos = entrada.nextInt();
		BigInteger n1, f1, d1, n2, f2, d2, q, d, s0, t0, m, n, l1, l2, u1, u2;
		for(int i = 1; i <= casos; i++){
			n1 = entrada.nextBigInteger();
			f1 = entrada.nextBigInteger();
			d1 = entrada.nextBigInteger();
			n2 = entrada.nextBigInteger();
			f2 = entrada.nextBigInteger();
			d2 = entrada.nextBigInteger();
			ArrayList<BigInteger>  info = euclides(d1, d2);
			d = info.get(0);
			s0 = info.get(1);
			t0 = info.get(2);
			q = f2.subtract(f1).divide(d);
			m = d2.divide(d);
			n = d1.divide(d);
			l1 = techo(s0.multiply(q).negate(), m);
			l2 = techo(t0.multiply(q), n);
			u1 = piso(n1.subtract(uno).subtract(s0.multiply(q)) , m);
			u2 = piso(n2.subtract(uno).add(t0.multiply(q)), n);
			System.out.println(u1.min(u2).subtract(l1.max(l2)).add(uno));
		}
	}
}