struct CombMod {
    fact: Vec<Mint>,
    fact_inv: Vec<Mint>
}

impl CombMod {
    fn new(n: usize) -> CombMod {
        let mut fact = vec![Mint::new(1); n+1];
        let mut fact_inv = vec![Mint::new(1); n+1];
        for i in 0..n {
            fact[i+1] = fact[i] * Mint::new((i+1) as i64);
        }

        fact_inv[n] = fact[n].inv();
        for i in (0..n).rev() {
            fact_inv[i] = fact_inv[i+1] * Mint::new((i+1) as i64);
        }

        CombMod { fact, fact_inv }
    }

    fn calc(&self, n: usize, k: usize) -> Mint{
        if n < k { return Mint::new(0); }
        self.fact[n] * self.fact_inv[n-k] * self.fact_inv[k]
    }
}
