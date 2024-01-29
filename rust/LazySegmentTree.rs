pub trait Monoid: Clone {
    fn e() -> Self;

    fn op(&self, b: &Self) -> Self;
}

pub trait Mapping<S>: Monoid {
    fn mapping(&self, rhs: &S) -> S;
}

pub struct LazySegmentTree<S, F> {
    n: usize,
    log: u32,
    node: Vec<S>,
    lazy: Vec<F>
}

impl<S: Monoid, F: Mapping<S>> LazySegmentTree<S, F> {
    pub fn new(mut n: usize) -> LazySegmentTree<S, F> {
        n = n.next_power_of_two();
        LazySegmentTree {
            n,
            log: n.trailing_zeros(),
            node: vec![S::e(); 2*n],
            lazy: vec![F::e(); n],
        }
    }

    pub fn apply<R>(&mut self, rng: R, f: F)
    where R: RangeBounds<usize>
    {
        let (mut l, mut r) = self.get_bound(rng);
        self.range_propagate(l..r);
        l += self.n;
        r += self.n;
        {
            let mut l = l;
            let mut r = r;
            while l < r {
                if l&1 == 1 {
                    self.node[l] = f.mapping(&self.node[l]);
                    if l < self.n {
                        self.lazy[l] = self.lazy[l].op(&f);
                    }
                    l += 1;
                }
                if r&1 == 1 {
                    r -= 1;
                    self.node[r] = f.mapping(&self.node[r]);
                    if r < self.n {
                        self.lazy[r] = self.lazy[r].op(&f);
                    }
                }
                l >>= 1;
                r >>= 1;
            }
        }

        for i in l.trailing_zeros()+1..=self.log {
            let v = l>>i;
            self.node[v] = self.node[2*v].op(&self.node[2*v+1]);
        }
        for i in r.trailing_zeros()+1..=self.log {
            let v = r-1>>i;
            self.node[v] = self.node[2*v].op(&self.node[2*v+1]);
        }
    }

    pub fn get(&mut self, x: usize) -> S {
        assert!(x < self.n);
        self.range_propagate(x..=x);
        self.node[x+self.n].clone()
    }

    pub fn set(&mut self, mut x: usize, v: S) {
        assert!(x < self.n);
        self.range_propagate(x..=x);
        x += self.n;
        self.node[x] = v;
        while x > 1 {
            x >>= 1;
            self.node[x] = self.node[2*x].op(&self.node[2*x+1]);
        }
    }

    pub fn query<R>(&mut self, rng: R) -> S
    where R: RangeBounds<usize>
    {
        let (mut l, mut r) = self.get_bound(rng);
        assert!(l <= r && r <= self.n);
        self.range_propagate(l..r);

        l += self.n;
        r += self.n;

        let mut ans_l = S::e();
        let mut ans_r = S::e();
        while l < r {
            if l&1 == 1 {
                ans_l = ans_l.op(&self.node[l]);
                l += 1;
            }
            if r&1 == 1 {
                r -= 1;
                ans_r = self.node[r].op(&ans_r);
            }

            l >>= 1;
            r >>= 1;
        }

        ans_l.op(&ans_r)
    }

    fn range_propagate<R>(&mut self, rng: R)
    where R: RangeBounds<usize>
    {
        let (mut l, mut r) = self.get_bound(rng);
        l += self.n;
        r += self.n;
        for i in (l.trailing_zeros()+1..=self.log).rev() {
            self.propagate(l>>i);
        }
        for i in (r.trailing_zeros()+1..=self.log).rev() {
            self.propagate(r-1>>i);
        }
    }

    fn propagate(&mut self, k: usize) {
        debug_assert!(k < self.n);
        self.node[2*k] = self.lazy[k].mapping(&self.node[2*k]);
        self.node[2*k + 1] = self.lazy[k].mapping(&self.node[2*k + 1]);
        if 2*k < self.n {
            self.lazy[2*k] = self.lazy[2*k].op(&self.lazy[k]);
            self.lazy[2*k + 1] = self.lazy[2*k + 1].op(&self.lazy[k]);
        }
        self.lazy[k] = F::e();
    }

    fn get_bound<R: RangeBounds<usize>>(&self, rng: R) -> (usize, usize) {
        let l = match rng.start_bound() {
            std::ops::Bound::Excluded(&v) => v+1,
            std::ops::Bound::Included(&v) => v,
            std::ops::Bound::Unbounded => 0,
        };
        let r = match rng.end_bound() {
            std::ops::Bound::Excluded(&v) => v,
            std::ops::Bound::Included(&v) => v+1,
            std::ops::Bound::Unbounded => self.n,
        };
        (l, r)
    }
}
