pub trait Monoid: Clone {
    fn e() -> Self;

    fn op(&self, rhs: &Self) -> Self;
}

struct SegTree2D<T: Monoid> {
    h: usize,
    w: usize,
    data: Vec<T>
}

impl<T: Monoid> SegTree2D<T> {
    #[inline]
    fn id(&self, i: usize, j: usize) -> usize {
        i*2*self.w + j
    }

    fn new(h: usize, w: usize) -> Self {
        let h = h.next_power_of_two();
        let w = w.next_power_of_two();
        let data = vec![T::e(); 4*h*w];
        Self {
            h,
            w,
            data,
        }
    }

    fn set(&mut self, mut i: usize, mut j: usize, val: T) {
        assert!(i < self.h && j < self.w);
        i += self.h;
        j += self.w;

        let id = self.id(i, j);
        self.data[id] = val;

        let mut w = j>>1;
        while w > 0 {
            let id = self.id(i, w);
            self.data[id] = self.data[self.id(i, w<<1)].op(&self.data[self.id(i, w<<1 | 1)]);
            w >>= 1;
        }

        let mut h = i>>1;
        while h > 0 {
            let id = self.id(h, j);
            self.data[id] = self.data[self.id(h << 1, j)].op(&self.data[self.id(h<<1 | 1, j)]);
            let mut w = j>>1;
            while w > 0 {
                let id = self.id(h, w);
                self.data[id] = self.data[self.id(h, w << 1)].op(&self.data[self.id(h, w<<1 | 1)]);
                w >>= 1;
            }
            h >>= 1;
        }
    }

    fn query<R>(&self, rng: R) -> T
    where R: std::ops::RangeBounds<(usize, usize)>
    {
        let (mut li, mut lj) = match rng.start_bound() {
            std::ops::Bound::Excluded(&(i, j)) => (i+1, j+1),
            std::ops::Bound::Included(&(i, j)) => (i, j),
            std::ops::Bound::Unbounded => (0, 0),
        };
        let (mut ri, mut rj) = match rng.end_bound() {
            std::ops::Bound::Excluded(&(i, j)) => (i, j),
            std::ops::Bound::Included(&(i, j)) => (i+1, j+1),
            std::ops::Bound::Unbounded => (0, 0),
        };
        assert!(li <= ri && ri <= self.h);
        assert!(lj <= rj && rj <= self.w);
        let mut ans = T::e();

        li += self.h;
        lj += self.w;
        ri += self.h;
        rj += self.w;

        let mut lh = li;
        let mut rh = ri;
        while lh < rh {
            if lh&1 == 1 {
                let mut lw = lj;
                let mut rw = rj;
                while lw < rw {
                    if lw&1 == 1 {
                        ans = ans.op(&self.data[self.id(lh, lw)]);
                        lw += 1;
                    }
                    if rw&1 == 1 {
                        rw -= 1;
                        ans = ans.op(&self.data[self.id(lh, rw)]);
                    }

                    lw >>= 1;
                    rw >>= 1;
                }
                lh += 1;
            }
            if rh&1 == 1 {
                rh -= 1;
                let mut lw = lj;
                let mut rw = rj;
                while lw < rw {
                    if lw&1 == 1 {
                        ans = ans.op(&self.data[self.id(rh, lw)]);
                        lw += 1;
                    }
                    if rw&1 == 1 {
                        rw -= 1;
                        ans = ans.op(&self.data[self.id(rh, rw)]);
                    }

                    lw >>= 1;
                    rw >>= 1;
                }
            }

            lh >>= 1;
            rh >>= 1;
        }

        ans
    }
}
