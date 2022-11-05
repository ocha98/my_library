struct UnionFind {
    par: Vec<i32>,
}

#[allow(dead_code)]
impl UnionFind {
    fn new(n: usize) -> UnionFind {
        UnionFind {
            par: vec![-1; n]
        }
    }

    fn root(&mut self, x: usize) -> usize{
        if self.par[x] < 0 {
            return  x;
        }

        let p = self.root(self.par[x] as usize);
        self.par[x] = p as i32;
        p
    }

    fn size(&mut self, x: usize) -> i32 {
        let root = self.root(x);
        -self.par[root]
    }

    fn unite(&mut self, x: usize, y: usize) {
        let mut x = self.root(x);
        let mut y = self.root(y);

        if x == y {
            return;
        }

        if self.par[x] > self.par[y] {
            std::mem::swap(&mut x, &mut y);
        }

        self.par[x] += self.par[y];
        self.par[y] = x as i32;
    }

    fn same(&mut self, x: usize, y: usize) -> bool {
        self.root(x) == self.root(y)
    }
}
