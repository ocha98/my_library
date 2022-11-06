fn warshall_floyd(dist: &mut Vec<Vec<i64>>){
    let n = dist.len();
    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                if dist[i][k] == INF || dist[k][j] == INF{ continue; }
                dist[i][j] = dist[i][j].min(dist[i][k] + dist[k][j]);
            }
        }
    }
}
