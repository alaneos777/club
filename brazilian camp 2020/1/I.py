from sys import stdout,stdin
import math
 
def calc(n, m):
    if n == 0:
        return (m-1, 0)
    if m == 1:
        return (n, 0)
    if m == 2:
        xm = int((1 + math.sqrt(1+8*n))/2)
        for x in range(max(0, xm-10), xm+11):
            if n < x*(x-1)//2:
                return (x-1, n-(x-1)*(x-2)//2)
    a = m
    comb = 1
    while n - comb >= 0:
        comb = comb * (a+1) // (a+1-m)
        a = a+1
    return (a-1, n - comb*(a-m)//a)
 
lista = [int(i) for i in stdin.readline().split()]
n = lista[0]
M = lista[1]
 
m = M
while m>=1:
    par = calc(n, m)
    stdout.write(str(par[0]) + " ")
    n = par[1]
    m = m-1
stdout.write("\n")