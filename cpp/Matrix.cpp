template<typename T>
struct Matrix {
    private:
    vector<vector<T>> data;
    int h, w;
    public:
    Matrix(){}
    Matrix(int h, int w, T val=0): data(h, vector<T>(w, val)),h(h), w(w){}

    Matrix unit() const {
        assert(h == w);
        Matrix<T> retu(h, w);
        for(int i = 0;i < h; ++i){
            retu[i][i] = 1;
        }
        return retu;
    }

    const vector<T>& operator[](int i) const {
        return data[i];
    }

    vector<T>& operator[](int i){
        return data[i];
    }

    Matrix operator*(const Matrix& a) const {
        assert(w == a.h);
        Matrix<T> retu(h, a.w);
        for(int i = 0;i < h; ++i){
            for(int j = 0;j < a.w; ++j){
                for(int k = 0;k < w; ++k){
                    retu[i][j] += data[i][k] * a[k][j];
                }
            }
        }
        return retu;
    }

    Matrix pow(long long n) const {
        assert(h == w);
        Matrix retu = Matrix(h,h).unit();
        Matrix x = *this;
        while(n != 0){
            if(n&1){
                retu = retu * x;
            }
            x = x * x;
            n >>= 1;
        }
        return retu;
    }
};