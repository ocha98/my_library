#[derive(Copy, Clone)]
struct Mint {
    v: i64,
}

#[allow(dead_code)]
impl Mint {
    fn new(mut v: i64) -> Mint {
        v %= MOD;
        if v < 0 {
            v += MOD;
        }
        Mint { v }
    }

    fn zero() -> Mint {
        Mint { v: 0 }
    }

    fn pow(&self, mut n: i64) -> Mint {
        let mut resu = Mint::new(1);
        let mut x = *self;
        while n > 0 {
            if n & 1 == 1 {
                resu *= x;
            }
            x *= x;
            n >>= 1;
        }
        resu
    }

    fn inv(&self) -> Mint {
        self.pow(MOD - 2)
    }
}

impl std::ops::Add for Mint {
    type Output = Self;
    fn add(self, rhs: Self) -> Self {
        let mut retu = self.clone();
        retu += rhs;
        retu
    }
}

impl std::ops::Sub for Mint {
    type Output = Self;
    fn sub(self, rhs: Self) -> Self {
        let mut retu = self.clone();
        retu -= rhs;
        retu
    }
}

impl std::ops::Mul for Mint {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self {
        let mut retu = self.clone();
        retu *= rhs;
        retu
    }
}

impl std::ops::Div for Mint {
    type Output = Self;
    fn div(self, rhs: Self) -> Self {
        let mut retu = self.clone();
        retu /= rhs;
        retu
    }
}

impl std::ops::AddAssign for Mint {
    fn add_assign(&mut self, rhs: Self) {
        self.v += rhs.v;
        if self.v >= MOD {
            self.v -= MOD;
        }
    }
}

impl std::ops::SubAssign for Mint {
    fn sub_assign(&mut self, rhs: Self) {
        self.v += MOD - rhs.v;
        if self.v >= MOD {
            self.v -= MOD;
        }
    }
}

impl std::ops::MulAssign for Mint {
    fn mul_assign(&mut self, rhs: Self) {
        self.v *= rhs.v;
        self.v %= MOD;
    }
}

impl std::ops::DivAssign for Mint {
    fn div_assign(&mut self, rhs: Self) {
        *self *= rhs.inv();
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
