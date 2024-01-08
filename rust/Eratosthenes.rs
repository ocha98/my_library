#[allow(dead_code)]
struct Eratosthenes {
    min_factor: Vec<usize>,
    primes: Vec<usize>,
    n: usize
}

#[allow(dead_code)]
impl Eratosthenes {
    fn new(n: usize) -> Self {
        let mut min_factor = vec![0; n+1];
        let mut primes = vec![];
        min_factor[1] = 1;
        for i in 2..=n {
            if min_factor[i] == 0 {
                min_factor[i] = i;
                primes.push(i);
            }

            for p in &primes {
                if p*i > n || *p > min_factor[i] { break; }
                min_factor[p*i] = *p;
            }
        }

        Eratosthenes { min_factor, primes, n }
    }

    fn is_prime(&self, n: usize) -> bool {
        assert!(n <= self.n);
        if n == 1 || n == 0 { return false; }
        return n == self.min_factor[n];
    }

    fn factorize(&self, mut n: usize) -> Vec<(usize, i32)>{
        assert!(1 <= n && n <= self.n);
        let mut res = vec![];
        while n > 1 {
            let p = self.min_factor[n];
            let mut e = 0;
            while self.min_factor[n] == p {
                n /= p;
                e += 1;
            }
            res.push((p, e));
        }
        res
    }

    fn divisors(&self, n: usize) -> Vec<usize> {
        assert!(1 <= n && n <= self.n);
        let mut res = vec![1];
        let factors = self.factorize(n);

        for (p, e) in factors {
            let s = res.len();
            for i in 0..s {
                let mut v = 1;
                for _ in 0..e {
                    v *= p;
                    res.push(res[i]*v);
                }
            }
        }

        res
    }
}
