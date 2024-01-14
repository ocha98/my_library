pub struct RollingHash {
    hash: Vec<u128>,
    power: Vec<u128>,
}


impl RollingHash {
    const MOD: u128 = (1<<61) - 1;

    pub fn new<T: Into<u128> + Copy>(s: &Vec<T>) -> Self {
        let n = s.len();
        let mut hash = vec![0; n+1];
        let mut power = vec![0; n+1];
        power[0] = 1;
        let base = RollingHash::get_base();
        let md = RollingHash::MOD;
        for i in 0..n {
            power[i+1] = power[i] * base % md;
            hash[i+1] = hash[i] * base % md + s[i].into();
            if hash[i+1] >= md { hash[i+1] -= md; }
        }

        Self {
            hash,
            power,
        }
    }

    pub fn get<R: std::ops::RangeBounds<usize>>(&self, rng: R) -> u128 {
        let l = match rng.start_bound() {
            std::ops::Bound::Excluded(&v) => v+1,
            std::ops::Bound::Included(&v) => v,
            std::ops::Bound::Unbounded => 0,
        };
        let r = match rng.end_bound() {
            std::ops::Bound::Excluded(&v) => v,
            std::ops::Bound::Included(&v) => v+1,
            std::ops::Bound::Unbounded => self.hash.len()-1,
        };

        let md = RollingHash::MOD;
        let mut retu = self.hash[r] + md - (self.hash[l] * self.power[r-l])%md;
        if retu >= md { retu -= md; }
        retu
    }

    // ハッシュをh1h2と連結する
    pub fn link(&self, h1: u128, h2: u128, len_h2: usize) -> u128 {
        let md = RollingHash::MOD;
        let mut resu = h1 * self.power[len_h2] % md + h2;
        if resu >= md { resu -= md; }
        resu
    }

    pub fn get_base() -> u128 {
        static BASE: std::sync::OnceLock<u128> = std::sync::OnceLock::new();
        *BASE.get_or_init(|| RollingHash::random_base())
    }

    fn random_base() -> u128 {
        use rand::Rng;
        use num::Integer;
        let r: u128 = 37;
        let mut rng = rand::thread_rng();
        loop {
            let k = rng.gen_range(1..RollingHash::MOD);
            if k.gcd(&(RollingHash::MOD-1)) != 1 {
                continue;
            }

            let b = RollingHash::pow_mod(r, k);
            if b <= 100 { continue; }
            
            return b;
        }
    }

    fn pow_mod(mut x: u128, mut n: u128) -> u128 {
        let mut ret = 1;
        x %= RollingHash::MOD;
        while  n > 0 {
            if n%2 == 1 {
                ret *= x;
                ret %= RollingHash::MOD;
            }
            x *= x;
            x %= RollingHash::MOD;
            n >>= 1;
        }
        ret
    }
}
