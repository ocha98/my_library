template <typename  T>
struct ComplexNumber{
    T real, image;

    ComplexNumber(T real = 0, T image = 0):real(real), image(image){}

    T abs()const {
        return sqrt(real*real + image*image);
    }

    T norm()const {
        return real*real + image*image;
    }

    ComplexNumber conj()const {
        return ComplexNumber(real, -image);
    }

    ComplexNumber operator*(const ComplexNumber& a)const {
        return ComplexNumber(*this) *= a;
    }

    ComplexNumber operator+(const ComplexNumber& a)const {
        return ComplexNumber(*this) += a;
    }

    ComplexNumber operator-(const ComplexNumber& a)const {
        return ComplexNumber(*this) -= a;
    }

    ComplexNumber operator/(const ComplexNumber& a)const {
        return ComplexNumber(*this) /= a;
    }

    ComplexNumber& operator+=(const ComplexNumber& a){
        this->real += a.real;
        this->image += a.image;
        return *this;
    }

    ComplexNumber& operator-=(const ComplexNumber& a){
        this->real -= a.real;
        this->image -= a.image;
        return *this;
    }

    ComplexNumber& operator*=(const ComplexNumber& a){
        this->real = real*a.real - image*a.image;
        this->image = real*a.image + image*a.real;
        return *this;
    }

    ComplexNumber& operator/=(const ComplexNumber& a){
        T x = a.real*a.real + a.image*a.image;
        this->real = (real*a.real + image*a.image) / x;
        this-> image = (image*a.real - real*a.image) / x;
        return *this;
    }

    bool operator==(const ComplexNumber& a)const {
        return real == a.real && image == a.image;
    }

    bool operator!=(const ComplexNumber& a)const {
        return !(*this == a);
    }

    bool operator<(const ComplexNumber& a) const {
        if (real == a.real){
            return image < a.image;
        }
        return real < a.real;
    }
};