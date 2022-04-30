template <typename  T>
struct ComplexNumber{
    T real, image;

    ComplexNumber(T real, T image):real(real), image(image){}
    ComplexNumber(T real):real(real), image(0){}
    ComplexNumber():real(0), image(0){}

    double abs()const {
        return sqrt(real*real + image*image);
    }

    T abs2()const {
        return real*real + image*image;
    }

    ComplexNumber conj() const{
        return ComplexNumber(real, -image);
    }

    ComplexNumber operator*(const ComplexNumber& a)const {
        return ComplexNumber(real*a.real - image*a.image, real*a.image + a.real*image);
    }

    ComplexNumber operator+(const ComplexNumber& a)const {
        return ComplexNumber(real + a.real, image + a.image);
    }

    ComplexNumber operator-(const ComplexNumber& a)const {
        return ComplexNumber(real - a.real, image - a.image);
    }

    ComplexNumber operator/(const ComplexNumber& a)const {
        auto b = a.real*a.real + a.image*a.image;
        return ComplexNumber((real*a.real + image*a.image)/b, (a.real*image - real*a.image)/b);
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
        ComplexNumber x = (*this) * a;
        this->real = x.real;
        this->image = x.image;
        return *this;
    }

    ComplexNumber& operator/=(const ComplexNumber& a){
        ComplexNumber x = *this / a;
        this->real = x.real;
        this-> image = x.image;
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