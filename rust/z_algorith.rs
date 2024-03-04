fn z_algorith(s: &[char]) -> Vec<usize> {
    let n = s.len();
    let mut z = vec![0; n];
    z[0] = n;
    let mut i = 1;
    let mut j = 0;
    while i < n {
        while i+j < n && s[j] == s[i+j] {
            j += 1;
        }
        z[i] = j;
        if j == 0 {
            i += 1;
            continue;
        }

        let mut k = 1;
        while k < j && k + z[k] < j {
            z[i+k] = z[k];
            k += 1;
        }

        i += k;
        j -= k;
    }

    z
}
