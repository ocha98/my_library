fn extgcd(a: i64, b: i64) -> (i64, i64) {
    // ax + by = gcd(a, b)
    if a == 0 { return (0, 1); }
    if b == 0 { return (1, 0); }
    let q = a/b;
    let r = a%b;
    let (s, t) = extgcd(b, r);

    let y = s - q*t;
    (t, y)
}
