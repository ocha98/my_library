const MOD: i64 = 998244353;

#[derive(Copy, Clone)]
struct Mint {
    v: i64,
}

impl Mint {
    fn new(mut v: i64) -> Mint{
        v %= MOD;
        v += MOD;
        v %= MOD;
        Mint { v }
    }

    fn pow(&self, mut n: i64) -> Mint{
        let mut resu = Mint::new(1);
        let mut x = *self;
        while n > 0 {
            if n & 1 == 1 {
                resu *= x;
            }
            x *= x;
            n /= 2;
        }
        resu
    }

    fn inv(&self) -> Mint {
        self.pow(MOD - 2)
    }
}

impl std::ops::Add for Mint {
    type Output = Self;
    fn add(self, other: Self) -> Self {
        Mint::new((self.v + other.v)%MOD)
    }
}

impl std::ops::Sub for Mint {
    type Output = Self;
    fn sub(self, other: Self) -> Self {
        Mint::new((self.v - other.v + MOD)%MOD)
    }
}

impl std::ops::Mul for Mint {
    type Output = Self;
    fn mul(self, other: Self) -> Self {
        Mint::new(self.v*other.v % MOD)
    }
}

impl std::ops::Div for Mint {
    type Output = Self;
    fn div(self, other: Self) -> Self {
        self*other.inv()
    }
}

impl std::ops::AddAssign for Mint {
    fn add_assign(&mut self, other: Self) {
        *self = *self + other;
    }
}

impl std::ops::MulAssign for Mint {
    fn mul_assign(&mut self, rhs: Self) {
        *self = *self * rhs;
    }
}

impl std::ops::DivAssign for Mint {
    fn div_assign(&mut self, rhs: Self) {
        *self = *self / rhs;
    }
}

impl std::str::FromStr for Mint {
    type Err = std::num::ParseIntError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let v = s.parse().unwrap();
        Ok(Mint::new(v))
    }
}

impl std::fmt::Display for Mint {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.v)
    }
}
