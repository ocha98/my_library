fn divisors(n: i64) -> Vec<i64> {
    let mut retu = vec![];
    for i in 1.. {
        if i*i > n { break; }
        if n%i != 0 { continue; }
        if i*i == n {
            retu.push(i);
        } else {
            retu.push(i);
            retu.push(n/i);
        }
    }

    retu
}
