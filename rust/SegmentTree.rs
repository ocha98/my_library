struct  SegmentTree<T, F> {
    n: usize,
    e: T,
    node: Vec<T>,
    op: F
}

#[allow(dead_code)]
impl<T: Clone + Copy, F: Fn(T, T) -> T> SegmentTree<T, F> {
    pub fn new(mut n: usize, e: T, op: F) -> SegmentTree<T, F> {
        n = n.next_power_of_two();
        SegmentTree{
            n,
            e,
            node: vec![e; 2*n],
            op
        }
    }

    pub fn set(&mut self, i: usize, val: T) {
        assert!(i < self.n);
        self.node[i + self.n] = val;
    }

    pub fn build(&mut self) {
        for k in (1..self.n).rev() {
            self.node[k] = (self.op)(self.node[k<<1], self.node[k<<1 | 1]);
        }
    }

    pub fn update(&mut self, mut i: usize, val: T) {
        assert!(i < self.n);
        i += self.n;

        self.node[i] = val;
        while i > 1 {
            i >>= 1;
            self.node[i] = (self.op)(self.node[i<<1], self.node[i<<1 | 1]);
        }
    }

    pub fn query(&self, mut l: usize, mut r: usize) -> T {
        assert!(l <= self.n);
        assert!(r <= self.n);

        l += self.n;
        r += self.n;

        let mut ans_l = self.e;
        let mut ans_r = self.e;
        while l < r {
            if l&1 == 1 {
                ans_l = (self.op)(ans_l, self.node[l]);
                l += 1;
            }
            if r&1 == 1 {
                r -= 1;
                ans_r = (self.op)(self.node[r], ans_r);
            }
            l >>= 1;
            r >>= 1;
        }

        (self.op)(ans_l, ans_r)
    }

    pub fn get(&self, i: usize) -> T {
        assert!(i < self.n);
        self.node[i + self.n]
    }
}
