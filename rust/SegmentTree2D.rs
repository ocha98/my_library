pub trait Monoid: Clone {
    fn e() -> Self;

    fn op(&self, rhs: &Self) -> Self;
}

struct SegTree2D<T: Monoid> {
    h: usize,
    w: usize,
    data: Vec<Vec<T>>
}

impl<T: Monoid> SegTree2D<T> {
    fn new(h: usize, w: usize) -> Self {
        let h = h.next_power_of_two();
        let w = w.next_power_of_two();
        let data = vec![vec![T::e(); 2*w]; 2*h];
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

        self.data[i][j] = val;

        let mut h = i>>1;
        while h > 0 {
            self.data[h][j] = self.data[h << 1][j].op(&self.data[h<<1 | 1][j]);
            h >>= 1;
        }

        let mut w = j>>1;
        while w > 0 {
            self.data[i][w] = self.data[i][w<<1].op(&self.data[i][w<<1 | 1]);
            let mut h = i>>1;
            while h > 0 {
                self.data[h][w] = self.data[h<<1][w].op(&self.data[h<<1 | 1][w]);
                h >>= 1;
            }
            w >>= 1;
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

        let mut lw = lj;
        let mut rw = rj;
        while lw < rw {
            if lw&1 == 1 {
                let mut lh = li;
                let mut rh = ri;
                while lh < rh {
                    if lh&1 == 1 {
                        ans = ans.op(&self.data[lh][lw]);
                        lh += 1;
                    }
                    if rh &1 == 1 {
                        rh -= 1;
                        ans = ans.op(&self.data[rh][lw]);
                    }

                    lh >>= 1;
                    rh >>= 1;
                }
                lw += 1;
            }
            if rw&1 == 1 {
                rw -= 1;
                let mut lh = li;
                let mut rh = ri;
                while lh < rh {
                    if lh&1 == 1 {
                        ans = ans.op(&self.data[lh][rw]);
                        lh += 1;
                    }
                    if rh &1 == 1 {
                        rh -= 1;
                        ans = ans.op(&self.data[rh][rw]);
                    }

                    lh >>= 1;
                    rh >>= 1;
                }
            }

            lw >>= 1;
            rw >>= 1;
        }

        ans
    }
}