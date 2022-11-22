struct Eratosthenes {
    min_factor: Vec<usize>,
}

impl Eratosthenes {
    fn new(n: usize) -> Self {
        let mut min_factor = vec![0; n+1];
        min_factor[1] = 1;
        for i in 2..=n {
            if min_factor[i] != 0 { continue; }
            let mut j = i;
            while j <= n {
                min_factor[j] = i;
                j += i;
            }
        }

        Eratosthenes { min_factor }
    }

    fn is_prime(&self, n: usize) -> bool {
        if n == 1 { return false; }
        return n == self.min_factor[n];
    }

    fn factorize(&self,mut n: usize) -> Vec<(usize, i32)>{
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

    fn divisors(&self,n: usize) -> Vec<usize> {
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
