vals={1:(set([1]),)}

def eff(n):
    minimum=1000
    if n not in vals:
        for i in range(1,n):
            for s1 in eff(i):
                for s2 in eff(n-i):
                    comb=s1.union(s2.union(set([n])))
                    if len(comb)<minimum:
                        minimum=len(comb)
                        res=[comb]
                    if len(comb)==minimum:
                        if comb not in res:
                            res.append(comb)
        vals[n]=tuple(res)
    return vals[n]
res=0
for i in range(1,101):
    res+=len(eff(i)[0])-1
print(res)
for i in range(1,101):
    x = sorted(eff(i)[0])
    print(F"{x},")