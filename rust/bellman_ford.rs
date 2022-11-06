#[derive(Clone)]
struct Edge{
    from: usize,
    to: usize,
    cost: i64,
}

fn bellman_ford(v: usize, start: usize,  es: &Vec<Edge>) -> Vec<i64> {
    //v: 頂点数
    let mut dist = vec![INF; v];

    dist[start] = 0;
    let mut update = true;
    while update {
        update = false;
        for e in es {

            if dist[e.from] == INF { continue; }

            if dist[e.to] > dist[e.from] + e.cost {
                update =  true;
                dist[e.to] = dist[e.from] + e.cost;
            }
        }
    }
    dist
}
