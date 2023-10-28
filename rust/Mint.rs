#[derive(Copy, Clone, Default)]
struct ModInt<const MOD: i64>(i64);

impl<const MOD: i64> ModInt<MOD> {
    fn new(mut v: i64) -> Self {
        v %= MOD;
        if v < 0 { v += MOD; }
        Self(v)
    }

    fn pow(&self, mut n: i64) -> Self {
        let mut resu = Self::new(1);
        let mut x = *self;
        if n < 0 {
            x = x.inv();
            n *= -1;
        }
        while n > 0 {
            if n & 1 == 1 {
                resu *= x;
            }
            x *= x;
            n >>= 1;
        }
        resu
    }

    fn inv(&self) -> Self {
        self.pow(MOD - 2)
    }
}

macro_rules! impl_ops {
    ($trait:ident, $fn:ident, $op:tt) => {
        impl<const MOD: i64> std::ops::$trait for ModInt<MOD> {
            type Output = Self;
            fn $fn(mut self, rhs: Self) -> Self {
                self $op rhs;
                self
            }
        }
    };
}

macro_rules! impl_from {
    ($($type:ty),*) => {
        $(
            impl<const MOD: i64> From<$type> for ModInt<MOD> {
                fn from(value: $type) -> Self {
                    Self::new(value as i64)
                }
            }
        )*
    };
}

impl_from!(i32, u32, i64, u64, isize, usize);

impl_ops!(Add, add, +=);
impl_ops!(Sub, sub, -=);
impl_ops!(Mul, mul, *=);
impl_ops!(Div, div, /=);

impl<const MOD: i64> std::ops::AddAssign for ModInt<MOD> {
    fn add_assign(&mut self, rhs: Self) {
        self.0 += rhs.0;
        if self.0 >= MOD { self.0 -= MOD; }
    }
}

impl<const MOD: i64> std::ops::SubAssign for ModInt<MOD> {
    fn sub_assign(&mut self, rhs: Self) {
        self.0 += MOD - rhs.0;
        if self.0 >= MOD { self.0 -= MOD; }
    }
}

impl<const MOD: i64> std::ops::MulAssign for ModInt<MOD> {
    fn mul_assign(&mut self, rhs: Self) {
        self.0 *= rhs.0;
        self.0 %= MOD;
    }
}

impl<const MOD: i64> std::ops::DivAssign for ModInt<MOD> {
    fn div_assign(&mut self, rhs: Self) {
        *self *= rhs.inv();
    }
}

impl<const MOD: i64> std::str::FromStr for ModInt<MOD> {
    type Err = std::num::ParseIntError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let v = s.parse()?;
        Ok(ModInt::new(v))
    }
}

impl<const MOD: i64> std::fmt::Display for ModInt<MOD> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.0)
    }
}
