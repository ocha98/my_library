#include <iostream>
using namespace std;

long long powMOD(long long x, long long n, long long MOD){
    long long ret = 1;
    x %= MOD;
    while (n > 0) {
        if (n & 1){
            ret *= x;
            ret %= MOD;
        }
        
        x *= x;
        x %= MOD;
        n >>= 1;
    }
    return ret;
}

long long mod_inverse(int x, int mod){
    /* 
    modは素数のみ
    フェルマーの小定理
    参考:https://qiita.com/drken/items/6b4031ccbb2cab7436f3
    */

   return powMOD(x, mod-2, mod);
}


int main(){
    cout << mod_inverse(10, 1e9+7) << endl;
}