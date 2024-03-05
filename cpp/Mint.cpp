template<long long MOD>
struct Mint{
    private:
    long long val;

    public:
    constexpr Mint():val(0){}
    constexpr Mint(long long x){
        x %= MOD;
        if(x < 0)x += MOD;
        val = x;
    }

    constexpr Mint operator*(const Mint& a)const { return Mint(*this) *= a; }
    constexpr Mint operator/(const Mint& a)const { return Mint(*this) /= a; }
    constexpr Mint operator+(const Mint& a)const { return Mint(*this) += a; }
    constexpr Mint operator-(const Mint& a)const { return Mint(*this) -= a; }

    constexpr Mint operator-()const {
        Mint x(*this);
        if(x.val != 0){
            x.val = MOD - x.val;
        }
        return x;
    }

    constexpr Mint& operator++(){
        *this += 1;
        return *this;
    }

    constexpr Mint operator++(int){
        Mint x(*this);
        ++(*this);
        return x;
    }

    constexpr Mint& operator--(){
        *this -= 1;
        return *this;
    }

    constexpr Mint operator--(int){
        Mint x(*this);
        --(*this);
        return x;
    }

    constexpr Mint& operator+= (const Mint &a){
        this->val += a.val;
        if(this->val >= MOD)this->val -= MOD;
        return *this;
    }

    constexpr Mint& operator-= (const Mint &a){
        this->val +=  MOD - a.val;
        if(this->val >= MOD)this->val -= MOD;
        return *this;
    }

    constexpr Mint& operator*= (const Mint &a){
        this->val *= a.val;
        this->val %= MOD;
        return *this;
    }

    constexpr Mint& operator/= (const Mint & a){
        *this *= a.inv();
        return *this;
    }

    constexpr Mint pow(long long n)const {
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

    constexpr Mint inv()const{ return pow(MOD - 2); }
    constexpr long long get() const { return this->val; }
    constexpr long long mod() const { return MOD; }
};

template<long long MOD>
istream& operator>>(istream& is, Mint<MOD>& a){
    long long val;
    is >> val;
    a = val;
    return is;
}

template<long long MOD>
ostream& operator<<(ostream& os, const Mint<MOD>& a){
    return os << a.get();
}

using mint = Mint<998244353>;
