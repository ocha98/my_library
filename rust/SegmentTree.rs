pub trait Monoid {
    fn e() -> Self;

    fn op(&self, rhs: &Self) -> Self;
}

pub struct  SegmentTree<M> {
    n: usize,
    node: Vec<M>,
}

impl<M: Monoid + Clone> From<&Vec<M>> for SegmentTree<M> {
    fn from(value: &Vec<M>) -> Self {
        let n = value.len();
        let mut tree = SegmentTree::new(n);
        for i in 0..n {
            tree.set(i, value[i].clone());
        }

        tree
    }
}

impl<M: Monoid> SegmentTree<M> {
    pub fn new(mut n: usize) -> SegmentTree<M> {
        n = n.next_power_of_two();
        let node = (0..2*n).map(|_| M::e()).collect();
        SegmentTree{
            n,
            node,
        }
    }

    pub fn set(&mut self, mut i: usize, val: M) {
        assert!(i < self.n);
        i += self.n;

        self.node[i] = val;
        while i > 1 {
            i >>= 1;
            self.node[i] = self.node[i<<1].op(&self.node[i<<1 | 1]);
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
        assert!(l <= r && r <= self.n);

        l += self.n;
        r += self.n;

        let mut ans_l = M::e();
        let mut ans_r = M::e();
        while l < r {
            if l&1 == 1 {
                ans_l = ans_l.op(&self.node[l]);
                l += 1;
            }
            if r&1 == 1 {
                r -= 1;
                ans_r = self.node[r].op(&ans_r)
            }
            l >>= 1;
            r >>= 1;
        }

        ans_l.op(&ans_r)
    }

    pub fn get(&self, i: usize) -> &M {
        assert!(i < self.n);
        &self.node[i + self.n]
    }
}
