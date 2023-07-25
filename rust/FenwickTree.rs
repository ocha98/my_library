struct FenwickTree<T> {
    data: Vec<T>,
    n: usize
}

#[allow(dead_code)]
impl<T> FenwickTree<T>
where
    T: Copy + Clone + Default + std::ops::AddAssign + std::ops::Sub + std::ops::Sub<Output = T>
{
    fn new(n: usize) -> FenwickTree<T> {
        FenwickTree {
            data: vec![T::default(); n + 1],
            n
        }
    }

    fn add(&mut self, mut i: usize, x: T) {
        assert!(i < self.n);
        i += 1;
        while i <= self.n {
            self.data[i] += x;
            i += i & i.overflowing_neg().0;
        }
    }

    // sum[0, i)
    fn internal_sum(&self, mut i: usize) -> T {
        assert!(i <= self.n);
        let mut ret_sum = T::default();
        while i > 0 {
            ret_sum += self.data[i];
            i -= i & i.overflowing_neg().0;
        }

        ret_sum
    }

    // sum[l, r)
    fn sum<R>(&self, rng: R) -> T
    where R: std::ops::RangeBounds<usize>
    {
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

        assert!(l <= self.n);
        assert!(r <= self.n);
        assert!(l <= r);

        self.internal_sum(r) - self.internal_sum(l)
    }

    fn get(&self, i: usize) -> T {
        assert!(i < self.n);
        self.sum(i..i+1)
    }
}
