from sys import stdin, stdout

MX = 700

rel = []
sig = []
sub = []
padre = []
suma = []
ultimo_hijo = []

dp = []
dp_g = []

# INIT
i = 0
while(i < MX + 5):
    rel.append([])
    dp.append([])
    dp_g.append([])
    sig.append(0)
    sub.append(0)
    padre.append(0)
    suma.append(0)
    ultimo_hijo.append(0)

    j = 0
    while(j < MX + 5):
        dp[i].append(-1)
        dp_g[i].append(-1)
        j += 1

    i += 1
# FIN INIT

def dfs(nodo):
    # global sub
    # global padre
    # global sig
    # global rel

    sub[nodo] = 1
    ant = -1
    for s in rel[nodo]:
        if(s != padre[nodo]):
            padre[s] = nodo
            dfs(s)
            sub[nodo] += sub[s]
            sig[s] = ant

            suma[s] = sub[s]
            if(ant != -1): suma[s] += suma[ant]

            ant = s
    ultimo_hijo[nodo] = ant

def f(nodo, k):
    # global dp
    # global sig
    # global sub

    if(nodo == -1):
        if(k > 0): return 0
        return 1

    if(dp[nodo][k] != -1): return dp[nodo][k]

    res = f(sig[nodo], k) * g(nodo, 0)

    minimo = k
    if(sig[nodo] != -1): minimo -= suma[sig[nodo]]

    c = minimo
    if(c < 0): c = 1
    while(c <= k and c <= sub[nodo]):
        aux = f(sig[nodo], k - c) * g(nodo, c)
        if(aux > res): res = aux
        c += 1
    dp[nodo][k] = res
    
    return res

def g(nodo, k):
    # global dp_g
    # global rel
    # global sub
    
    if(dp_g[nodo][k] != -1): return dp_g[nodo][k]

    hijo = ultimo_hijo[nodo]
    
    res = 1

    if(hijo != -1):
        if(k == 0):
            c = 1
            quien = 1
            while(c <= sub[nodo]):
                aux = f(hijo, c - 1) * c
                if(aux > res):
                    res = aux
                    quien = c
                c += 1
        else:
            res = f(hijo, k - 1)

    dp_g[nodo][k] = res
    return res

n = int(stdin.readline())

i = 0
while(i < n - 1):
    a, b = stdin.readline().split(" ")
    a = int(a)
    b = int(b)

    rel[a].append(b)
    rel[b].append(a)

    i += 1

padre[1] = -1
sig[1] = -1
dfs(1)

stdout.write(str(g(1, 0)))
