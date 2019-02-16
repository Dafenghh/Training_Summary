import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.*;

public class Main
{
	int N = 200;

	BigInteger[][][] f,g,sum;
	BigInteger[] pw;

	public  Main() {
		f = new BigInteger[N][10][10];
		g = new BigInteger[N][10][10];
		sum = new BigInteger[N][10][10];

		for (int i = 0; i < N; i++)
		for (int j = 0; j < 10; j++)
		for (int k = 0; k < 10; k++)
			f[i][j][k] = g[i][j][k] = sum[i][j][k] = BigInteger.ZERO;

		pw = new BigInteger[N];
		pw[0] = BigInteger.valueOf(1);
		for (int i = 1; i < N; i++) pw[i] = pw[i-1].multiply(BigInteger.valueOf(10));	
		
		for (int i = 1; i < N; i++)
		for (int j = 0; j < 10; j++)
		for (int k = 0; k < 10; k++) {
			for (int t = 0; t < 10; t++) {
				if (j < k && k < t) f[i][j][k] = f[i][j][k].add(pw[i-1]);
				else f[i][j][k] = f[i][j][k].add(f[i-1][k][t]);
	
				g[i][j][k] = g[i][j][k].add(g[i-1][k][t]);
			}		
			if (j > 0) g[i][j][k] = f[i][j][k];
		}	
		
		for (int i = 1; i < N; i++) 
		for (int j = 0; j < 10; j++)
		for (int k = 0; k < 9; k++)
			sum[i][j][k+1] = sum[i][j][k].add(f[i][j][k]);		
	}
	
	BigInteger calc(BigInteger num) {
		num = num.add(BigInteger.ONE);
		String str = num.toString();
		int n = str.length();
		if (n <= 2) return BigInteger.ZERO;
		int[] digits = new int[n];
		for (int i = 0; i < n; i++) digits[i] = (int)(str.charAt(n-1-i) - '0');

		BigInteger acc = BigInteger.valueOf(0), res = BigInteger.valueOf(0);
		for (int k = 0; k < digits[n-1]; k++) res = res.add(g[n-1][0][k]);
		acc = acc.add(BigInteger.valueOf(digits[n-1]).multiply(pw[n-1]));

		for (int i = n - 2; i >= 0; i--) {
			if (i <= n - 3 && digits[i] > digits[i+1] && digits[i+1] > digits[i+2]) {
				res = res.add(sum[i][digits[i+1]][digits[i+1]+1]);
				acc = acc.add(BigInteger.valueOf(digits[i+1]+1).multiply(pw[i]));
				break;
			}
			res = res.add(sum[i][digits[i+1]][digits[i]]);
			acc = acc.add(BigInteger.valueOf(digits[i]).multiply(pw[i]));
		}
		res = res.add(num.subtract(acc));		
		return res;
	}

	public static void main (String[] args) 
	{
		Main solver = new Main();
		Scanner cin = new Scanner(System.in);

		double frac = cin.nextDouble();
		BigInteger p = BigInteger.valueOf((int)(frac * 100000)), q = BigInteger.valueOf(100000);
		BigInteger a = BigInteger.valueOf(10);
		for (;;) {
			BigInteger b = solver.calc(a);
			if (b.multiply(q).compareTo(a.multiply(p)) >= 0) break;
			BigInteger c = a.multiply(p).subtract(b.multiply(q)).add(q).subtract(p).subtract(BigInteger.ONE).divide(q.subtract(p));
			a = a.add(c);
		}
		System.out.println(a);
	}
}
