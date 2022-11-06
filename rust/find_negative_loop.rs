#[derive(Clone)]
struct Edge{
    from: usize,
    to: usize,
    cost: i64,
}


fn find_negative_loop(v: usize, es: &Vec<Edge>) -> bool{
    //v: 頂点数
    let mut dist = vec![0; v];

    for i in 0..v {
        for e in es {
            if dist[e.to] > dist[e.from] + e.cost {
                dist[e.to] = dist[e.from] + e.cost;
                if i == v-1 {
                    return true;
                }
            }
        }
    }

    false
}