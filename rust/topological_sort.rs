fn topological_sort(to: &Vec<Vec<usize>>) -> Vec<usize> {
    let n = to.len();
    let mut cnt = vec![0; n];
    for i in 0..n {
        for &v in &to[i] {
            cnt[v] += 1;
        }
    }

    let mut zero = VecDeque::new();
    for i in 0..n {
        if cnt[i] == 0 {
            zero.push_back(i);
        }
    }

    let mut sorted = vec![];
    while let Some(v) = zero.pop_front() {
        sorted.push(v);
        for &u in &to[v] {
            cnt[u] -= 1;
            if cnt[u] == 0 {
                zero.push_back(u);
            }
        }
    }

    sorted
}
