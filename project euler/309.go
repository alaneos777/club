package main
import(
	"fmt"
	"sort"
)

type pair struct{
	p, a int
}

func lpSieve(n int) []int {
	primes := make([]int, 0)
	lp := make([]int, n+1)
	for i := 2; i <= n; i++ {
		if lp[i] == 0 {
			lp[i] = i
			primes = append(primes, i)
		}
		for _, p := range primes {
			d := i * p
			if d > n {
				break
			}
			lp[d] = p
			if lp[i] == p {
				break
			}
		}
	}
	return lp
}

const L int = int(1e6)-1
var lp = lpSieve(L)

func factorice(n int) []pair{
	f := make([]pair, 0)
	for n > 1 {
		p, a := lp[n], 0
		for n % p == 0 {
			n /= p
			a++
		}
		f = append(f, pair{p, a})
	}
	return f
}

func getDivsSq(n int) []int {
	fact := factorice(n)
	divs := make([]int, 0)
	var dfs func(int, int)
	dfs = func(pos int, acum int){
		if pos == len(fact) {
			divs = append(divs, acum)
		}else{
			p, a := fact[pos].p, fact[pos].a*2
			p_pow := 1
			for i := 0; i <= a; i++ {
				dfs(pos + 1, acum * p_pow)
				p_pow *= p
			}
		}
	}
	dfs(0, 1)
	sort.Ints(divs)
	return divs
}

func main(){
	ans := 0
	for b := 1; b <= L; b++ {
		legs := make([]int, 0)
		for _, e := range getDivsSq(b) {
			d := b*b/e
			if d <= e {
				break
			}
			if (d+e)%2 == 1 {
				continue
			}
			l := (d+e)/2
			x := (d-e)/2
			if l <= L {
				legs = append(legs, x)
			}
		}
		for i := 0; i+1 < len(legs); i++ {
			for j := i+1; j < len(legs); j++ {
				if legs[i]*legs[j] % (legs[i] + legs[j]) == 0 {
					//h := legs[i]*legs[j] / (legs[i] + legs[j])
					ans++
					//fmt.Printf(" %d %d %d\n", legs[i], legs[j], h)
				}
			}
		}
	}
	fmt.Println(ans)
}