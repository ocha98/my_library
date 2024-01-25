pub trait Monoid: Clone {
    fn e() -> Self;

    fn op(a: &Self, b: &Self) -> Self;
}

pub struct  SegmentTree<M> {
    n: usize,
    node: Vec<M>,
}

impl<M: Monoid> SegmentTree<M> {
    pub fn new(mut n: usize) -> SegmentTree<M> {
        n = n.next_power_of_two();
        SegmentTree{
            n,
            node: vec![M::e(); 2*n],
        }
    }

    pub fn set(&mut self, i: usize, val: M) {
        assert!(i < self.n);
        self.node[i + self.n] = val;
    }

    pub fn build(&mut self) {
        for k in (1..self.n).rev() {
            self.node[k] = M::op(&self.node[k<<1], &self.node[k<<1 | 1]);
        }
    }

    pub fn update(&mut self, mut i: usize, val: M) {
        assert!(i < self.n);
        i += self.n;

        self.node[i] = val;
        while i > 1 {
            i >>= 1;
            self.node[i] = M::op(&self.node[i<<1], &self.node[i<<1 | 1]);
        }
    }

    pub fn query<R>(&self, rng: R) -> M
    where R: std::ops::RangeBounds<usize>
    {
        let mut l = match rng.start_bound() {
            std::ops::Bound::Excluded(&v) => v+1,
            std::ops::Bound::Included(&v) => v,
            std::ops::Bound::Unbounded => 0,
        };
        let mut r = match rng.end_bound() {
            std::ops::Bound::Excluded(&v) => v,
            std::ops::Bound::Included(&v) => v+1,
            std::ops::Bound::Unbounded => self.n,
        };

        assert!(l <= self.n);
        assert!(r <= self.n);

        l += self.n;
        r += self.n;

        let mut ans_l = M::e();
        let mut ans_r = M::e();
        while l < r {
            if l&1 == 1 {
                ans_l = M::op(&ans_l, &self.node[l]);
                l += 1;
            }
            if r&1 == 1 {
                r -= 1;
                ans_r = M::op(&self.node[r], &ans_r);
            }
            l >>= 1;
            r >>= 1;
        }

        M::op(&ans_l, &ans_r)
    }

    pub fn get(&self, i: usize) -> M {
        assert!(i < self.n);
        self.node[i + self.n].clone()
    }
}
