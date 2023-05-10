struct Mint{
    private:
    long long val;

    public:
    Mint(long long x){
        x %= MOD;
        if(x < 0)x += MOD;
        val = x;
    }
    Mint():val(0){}

    Mint operator*(const Mint& a)const {
        return Mint(*this) *= a;
    }

    Mint operator/(const Mint& a)const {
        return Mint(*this) /= a;
    }

    Mint operator+(const Mint& a)const {
        return Mint(*this) += a;
    }

    Mint operator-(const Mint& a)const {
        return Mint(*this) -= a;
    }

    Mint operator-()const {
        Mint x(*this);
        if(x.val != 0){
            x.val = MOD - x.val;
        }
        return x;
    }

    Mint& operator++(){
        *this += 1;
        return *this;
    }

    Mint operator++(int){
        Mint x(*this);
        ++(*this);
        return x;
    }

    Mint& operator--(){
        *this -= 1;
        return *this;
    }

    Mint operator--(int){
        Mint x(*this);
        --(*this);
        return x;
    }

    Mint& operator+= (const Mint &a){
        this->val += a.val;
        if(this->val >= MOD)this->val -= MOD;
        return *this;
    }

    Mint& operator-= (const Mint &a){
        this->val +=  MOD - a.val;
        if(this->val >= MOD)this->val -= MOD;
        return *this;
    }

    Mint& operator*= (const Mint &a){
        this->val *= a.val;
        this->val %= MOD;
        return *this;
    }

    Mint& operator/= (const Mint & a){
        *this *= a.inv();
        return *this;
    }

    Mint inv()const{
        return pow(MOD - 2);
    }

    Mint pow(long long n)const {
        if(n == 0)return 1;
        Mint retu(1);
        Mint x(*this);
        while(n != 0){
            if(n & 1){
                retu *= x;
            }
            x *= x;
            n >>= 1;
        }
        return retu;
    }

    long long get() const{
        return this->val;
    }
};

istream& operator>>(istream& is, Mint& a){
    long long val;
    is >> val;
    a = val;
    return is;
}

ostream& operator<<(ostream& os, const Mint& a){
    return os << a.get();
}