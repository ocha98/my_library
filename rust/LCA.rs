struct LCA<'a> {
    to: &'a Vec<Vec<usize>>,
    parent: Vec<Vec<Option<usize>>>,
    dist: Vec<usize>,
    k: usize,
    n: usize
}

#[allow(dead_code)]
impl<'a> LCA<'a> {
    fn new(to: &'a Vec<Vec<usize>>) -> LCA {
        let n = to.len();
        let mut k = 1;
        while (1<<k) < n {
            k += 1;
        }

        let parent = vec![vec![None; n]; k];
        let dist = vec![0; n];
        let mut retu = Self {
            to,
            parent,
            dist,
            k,
            n
        };

        retu.build();
        retu
    }

    fn build(&mut self) {
        self.dfs(0, None, 0);
        for i in 0..self.k-1 {
            for v in 0..self.n {
                if let Some(x) = self.parent[i][v] {
                    self.parent[i+1][v] = self.parent[i][x];
                } else {
                    self.parent[i+1][v] = None;
                }
            }
        }
    }

    fn dfs(&mut self, v: usize, p: Option<usize>, d: usize){
        self.parent[0][v] = p;
        self.dist[v] = d;
        for nxt in &self.to[v] {
            if Some(*nxt) != p {
                self.dfs(*nxt, Some(v), d+1);
            }
        }
    }

    fn get_lca(&self, mut u: usize, mut v: usize) -> usize {
        assert!(u < self.n);
        assert!(v < self.n);

        if self.dist[u] < self.dist[v] {
            std::mem::swap(&mut u, &mut v);
        }

        for i in 0..self.k {
            let diff = self.dist[u] - self.dist[v];
            if (diff >> i & 1) == 1 {
                u = self.parent[i][u].unwrap();
            }
        }

        if u == v {
            return u;
        }

        for i in (0..self.k).rev() {
            if self.parent[i][u] != self.parent[i][v] {
                u = self.parent[i][u].unwrap();
                v = self.parent[i][v].unwrap();
            }
        }

        self.parent[0][u].unwrap()
    }

    fn get_dist(&self, u: usize, v: usize) -> usize {
        assert!(u < self.n);
        assert!(v < self.n);

        let p = self.get_lca(u, v);

        self.dist[u] + self.dist[v] - 2*self.dist[p]
    }
}
