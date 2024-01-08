struct HLD<M: Monoid> {
    to: Vec<Vec<usize>>,
    head: Vec<usize>,
    par: Vec<usize>,
    to_seg_idx: Vec<usize>,
    tree: SegmentTree<M>,
}

#[allow(dead_code)]
impl<M: Monoid> HLD<M> {
    fn new(to: Vec<Vec<usize>>, w: &Vec<M>) -> Self {
        let n = to.len();
        let mut hld = Self {
            to,
            head: vec![0; n],
            par: vec![0; n],
            to_seg_idx: vec![0; n],
            tree: SegmentTree::new(n),
        };

        let mut size = vec![0; n];
        hld.dfs(0, n, &mut size);
        let mut idx = 0;
        hld.decomp(0, n, &mut idx);

        for i in 0..n {
            hld.tree.set(hld.to_seg_idx[i], w[i].clone());
        }
        hld.tree.build();
        hld
    }

    fn get(&self, v: usize) -> M {
        self.tree.get(self.to_seg_idx[v])
    }

    fn query(&mut self, mut u: usize, mut v: usize) -> M {
        let mut retu = M::e();
        while self.head[u] != self.head[v] {
            if self.to_seg_idx[self.head[u]] < self.to_seg_idx[self.head[v]] {
                std::mem::swap(&mut u, &mut v);
            }

            retu = M::op(&retu, &self.tree.query(self.to_seg_idx[self.head[u]], self.to_seg_idx[u] + 1));
            u = self.par[self.head[u]];
        }

        let l =  self.to_seg_idx[u].min(self.to_seg_idx[v]);
        let r = self.to_seg_idx[u].max(self.to_seg_idx[v]);
        M::op(&retu, &self.tree.query(l, r +1))
    }

    fn update(&mut self, i: usize, w: M) {
        self.tree.update(self.to_seg_idx[i], w);
    }

    fn dfs(&mut self, v: usize, par: usize, size: &mut Vec<usize>) {
        let n = self.to[v].len();
        if self.to[v].len() >= 2 && self.to[v][0] == par {
            self.to[v].swap(0, 1);
        }
        size[v] = 1;
        for i in 0..n {
            let nxt = self.to[v][i];
            if nxt == par { continue; }
            self.par[nxt] = v;
            self.dfs(nxt, v, size);
            size[v] += size[nxt];

            if size[nxt] > size[self.to[v][0]] {
                self.to[v].swap(i, 0);
            }
        }
    }

    fn decomp(&mut self, v: usize, par: usize, idx: &mut usize) {
        self.to_seg_idx[v] = *idx;
        *idx += 1;
        for i in 0..self.to[v].len() {
            let nxt = self.to[v][i];
            if nxt == par { continue; }
            if i == 0 {
                self.head[nxt] = self.head[v];
            } else {
                self.head[nxt] = nxt;
            }
            self.decomp(nxt, v, idx);
        }
    }
}
