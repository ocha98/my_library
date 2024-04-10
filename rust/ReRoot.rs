pub trait Monoid {
    fn e() -> Self;

    fn op(&self, rhs: &Self) -> Self;
}

pub struct ReRoot<M: Monoid> {
    n: usize,
    adj: Vec<Vec<usize>>,
    idx_for_adj: Vec<Vec<usize>>,
    _marker: std::marker::PhantomData<M>,
}

impl<M: Monoid> ReRoot<M> {
    pub fn new(n: usize) -> Self {
        Self {
            n,
            adj: vec![vec![]; n],
            idx_for_adj: vec![vec![]; n],
            _marker: std::marker::PhantomData
        }
    }

    pub fn add_edge(&mut self, u: usize, v: usize) {
        self.idx_for_adj[u].push(self.adj[v].len());
        self.idx_for_adj[v].push(self.adj[u].len());

        self.adj[u].push(v);
        self.adj[v].push(u);
    }

    fn dfs_preorder(&self) -> (Vec<usize>, Vec<usize>) {
        let mut st = vec![];
        let mut ord = vec![0; self.n];
        let mut par = vec![0; self.n];
        let mut k = 0;
        st.push(0);
        while let Some(v) = st.pop() {
            ord[k] = v;
            k += 1;
            for &nxt in &self.adj[v] {
                if nxt == par[v] { continue; }
                st.push(nxt);
                par[nxt] = v;
            }
        }

        (ord, par)
    }

    pub fn build(&mut self, add_node: &impl Fn(&M, usize) -> M) -> Vec<M> {
        let (ord, par) = self.dfs_preorder();

        let mut child_subtree_res = vec![];
        for i in 0..self.n {
            let vv: Vec<M> = (0..self.adj[i].len()).map(|_| M::e()).collect();
            child_subtree_res.push(vv);
        }

        for &v in ord[1..].iter().rev() {
            let p = par[v];

            let mut resu = M::e();
            let mut par_idx = 0;

            for (idx, &u) in self.adj[v].iter().enumerate() {
                if u == p {
                    par_idx = idx;
                    continue;
                }

                resu = resu.op(&child_subtree_res[v][idx]);
            }

            child_subtree_res[p][self.idx_for_adj[v][par_idx]] = add_node(&resu, v);
        }

        let mut node_res: Vec<M> = (0..self.n).map(|_| M::e()).collect();
        for &v in &ord {
            let m = self.adj[v].len();
            let mut acc_sum: Vec<M> = (0..m).map(|_| M::e()).collect();
            for i in (1..m).rev() {
                acc_sum[i-1] = acc_sum[i].op(&child_subtree_res[v][i]);
            }

            let mut sum = M::e();
            for i in 0..m {
                child_subtree_res[self.adj[v][i]][self.idx_for_adj[v][i]] = add_node(&sum.op(&acc_sum[i]), v);
                sum = sum.op(&child_subtree_res[v][i]);
            }

            node_res[v] = add_node(&sum, v);
        }

        node_res
    }
}
