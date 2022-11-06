struct WeightedUnionFind {
    par: Vec<i32>,
    weight: Vec<i32>,
}

#[allow(dead_code)]
impl WeightedUnionFind {
    fn new(n: usize) -> WeightedUnionFind {
        WeightedUnionFind {
            par: vec![-1; n],
            weight: vec![0; n],
        }
    }

    fn root(&mut self, x: usize) -> usize{
        if self.par[x] < 0 {
            return  x;
        }

        let p = self.root(self.par[x] as usize);
        self.weight[x] += self.weight[self.par[x] as usize];
        self.par[x] = p as i32;
        p
    }

    fn get_w(&mut self, x: usize) -> i32{
        self.root(x);
        self.weight[x]
    }

    fn diff(&mut self, x: usize, y: usize) -> i32{
        self.get_w(y) - self.get_w(x)
    }

    fn size(&mut self, x: usize) -> i32 {
        let root = self.root(x);
        -self.par[root]
    }

    fn merge(&mut self, x: usize, y: usize, mut w: i32) {
        w += self.get_w(x);
        w -= self.get_w(y);

        let mut x = self.root(x);
        let mut y = self.root(y);

        if x == y {
            return;
        }

        if self.par[x] > self.par[y] {
            std::mem::swap(&mut x, &mut y);
            w = -w;
        }

        self.par[x] += self.par[y];
        self.par[y] = x as i32;
        self.weight[y] = w;
    }

    fn same(&mut self, x: usize, y: usize) -> bool {
        self.root(x) == self.root(y)
    }
}
