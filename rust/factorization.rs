fn factorization(mut x: i64) -> Vec<(i64, i64)> {
    let mut resu = Vec::new();
    for i in 2.. {
        if i*i > x { break; }
        if x%i != 0{ continue; }

        let mut e = 0;
        while x%i == 0 {
            e += 1;
            x /= i;
        }

        resu.push((i, e));
    }

    if x != 1 {
        resu.push((x, 1));
    }

    resu
}