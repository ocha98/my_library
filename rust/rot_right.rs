fn rot_right<T: Clone>(a: &Vec<Vec<T>>) -> Vec<Vec<T>> {
    let rows = a.len();
    let cols = a[0].len();
    let mut rotated = vec![vec![a[0][0].clone(); rows]; cols];

    for i in 0..rows {
        for j in 0..cols {
            rotated[j][rows - 1 - i] = a[i][j].clone();
        }
    }

    rotated
}
