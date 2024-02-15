#[derive(Clone)]
struct Edge {
    to: usize,
    cap: u64,
    rev: usize,
}

pub struct Dinic {
    n: usize,
    es: Vec<Vec<Edge>>,
}

impl Dinic {
    pub fn new(n: usize) -> Self {
        Dinic {
            n,
            es: vec![vec![];n],
        }
    }

    pub fn add_edge(&mut self, from: usize, to: usize, cap: u64) {
        let rev = self.es[to].len();
        self.es[from].push(Edge { to, cap, rev });
        let rev = self.es[from].len()-1;
        self.es[to].push(Edge { to:from, cap: 0, rev });
    }

    pub fn max_flow(&mut self, s: usize, t: usize) -> u64 {
        let mut flow = 0;
        let mut idx = vec![0; self.n];
        loop {
            let level = self.bfs(s);
            if level[t] < 0 { return flow; }
            idx.fill(0);
            let mut f = self.dfs(s, t, std::u64::MAX, &mut idx, &level);
            while f > 0 {
                flow += f;
                f = self.dfs(s, t, std::u64::MAX, &mut idx, &level);
            }
        }
    }

    fn bfs(&mut self, s: usize) -> Vec<i32> {
        let mut level = vec![-1; self.n];
        level[s] = 0;
        let mut que = VecDeque::new();
        que.reserve(self.n);
        que.push_back(s);
        while let Some(v) = que.pop_front() {
            for e in &self.es[v] {
                if level[e.to] < 0 && e.cap > 0 {
                    level[e.to] = level[v] + 1;
                    que.push_back(e.to);
                }
            }
        }

        level
    }

    fn dfs(&mut self, v: usize, t: usize, f: u64, idx: &mut Vec<usize>, level: &Vec<i32>) -> u64{
        if v == t { return f; }
        let m = self.es[v].len();
        for i in idx[v]..m {
            idx[v] = i;
            let e = self.es[v][i].clone();
            if e.cap == 0 || level[v] >= level[e.to] { continue; }
            let d = self.dfs(e.to, t, f.min(e.cap), idx, level);
            if d > 0 {
                self.es[v][i].cap -= d;
                self.es[e.to][e.rev].cap += d;
                return d;
            }
        }

        0
    }
}
