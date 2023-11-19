fn grid_move_iter<'a>(i: usize, j: usize, h: usize, w: usize, d: &'a[(usize, usize)]) -> impl Iterator<Item = (usize, usize)> + 'a {
    d.iter().filter_map(move |&(di, dj)| {
        let ni = i.wrapping_add(di);
        let nj = j.wrapping_add(dj);
        if ni < h && nj < w {
            Some((ni, nj))
        } else {
            None
        }
    })
}
