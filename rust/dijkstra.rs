#[derive(Clone)]
struct Edge{
    to: usize,
    cost: i64,
}

fn dijkstra(start: usize, es: &Vec<Vec<Edge>>) -> Vec<i64>{
    let n = es.len();
    let mut dist = vec![INF; n];
    let mut que = std::collections::BinaryHeap::new();

    dist[start] = 0;
    que.push((-0, start));
    while let Some((mut w, v)) = que.pop() {
        w *= -1;
        if dist[v] < w { continue; }

        for e in &es[v] {
            if dist[e.to] > dist[v] + e.cost {
                dist[e.to] = dist[v] + e.cost;
                que.push((-dist[e.to], e.to));
            }
        }
    }

    dist
}
