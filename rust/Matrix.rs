#[derive(Clone)]
struct Matrix<T> {
    shape: (usize, usize),
    data: Vec<T>,
}

impl<T: Clone + Default> Matrix<T> {
    fn new(h: usize, w: usize) -> Self {
        Self {
            shape: (h, w),
            data: vec![T::default(); w*h],
        }
    }

    fn get(&self, i: usize, j: usize) -> T {
        assert!(i < self.shape.0 && j < self.shape.1);
        self.data[i*self.shape.1 + j].clone()
    }

    fn get_mut(&mut self, i: usize, j: usize) -> &mut T {
        assert!(i < self.shape.0 && j < self.shape.1);
        &mut self.data[i*self.shape.1 + j]
    }

    fn set(&mut self, i: usize, j: usize, data: T) {
        assert!(i < self.shape.0 && j < self.shape.1);
        self.data[i*self.shape.1 + j] = data;
    }
}

impl<T: Clone + Default> From<&Vec<Vec<T>>> for Matrix<T> {
    fn from(data: &Vec<Vec<T>>) -> Self {
        let h = data.len();
        let w = data[0].len();
        assert!(w > 0);
        let mut retu = Matrix {
            shape: (h, w),
            data: vec![T::default(); h*w],
        };
        for i in 0..h {
            for j in 0..w {
                retu.data[i*w + j] = data[i][j].clone();
            }
        }

        retu
    }
}

impl<T: Clone + Default + From<i32>> Matrix<T> {
    fn unit(n: usize) -> Self {
        let mut data = vec![T::default(); n*n];
        for i in 0..n {
            data[i*n + i] = 1.into();
        }

        Self {
            shape: (n, n),
            data,
        }
    }
}

impl<T: Clone + std::ops::AddAssign<T> + std::ops::Mul<T, Output=T> + Default> std::ops::Mul<&Matrix<T>> for &Matrix<T> {
    type Output = Matrix<T>;
    fn mul(self, rhs: &Matrix<T>) -> Matrix<T> {
        assert_eq!(self.shape.1, rhs.shape.0);
        let mut retu = Matrix::new(self.shape.0, rhs.shape.1);
        for i in 0..self.shape.0 {
            for k in 0..self.shape.1 {
                for j in 0..rhs.shape.1 {
                    *retu.get_mut(i, j) += self.get(i, k) * rhs.get(k, j);
                }
            }
        }

        retu
    }
}

impl<T: Clone + std::ops::Mul<T, Output=T> + Default + From<i32> + std::ops::AddAssign>  Matrix<T>{
    fn pow(&self, exp: u64) -> Self {
        assert_eq!(self.shape.0, self.shape.1);

        let mut retu = Self::unit(self.shape.0);
        let mut mul = self.clone();
        let mut exp = exp;
        while exp != 0 {
            if exp%2 == 1 {
                retu = &retu * &mul;
            }
            mul = &mul * &mul;
            exp /= 2;
        }

        retu
    }
}
