class KMP {
    private:
    vector<int> table;
    string pattern;

    vector<int> create_table(){
        assert(pattern.length() > 0);

        const int n = pattern.length();
        table.resize(n+1);
        table[0] = -1;
        int j = -1;
        for(int i = 0;i < n; ++i){
            while(j >= 0 && pattern[i] != pattern[j]){
                j = table[j];
            }
            ++j;
            table[i+1] = j;
        }

        return table;
    }

    public:
    void set_pattern(string s){
        pattern = s;
        create_table();
    }

    KMP(string pattern): pattern(pattern){
        set_pattern(pattern);
    }

    KMP(){}

    vector<int> search(const string& s) const {
        assert(table.size() > 0);
        const int n = s.length();
        const int m = pattern.length();

        vector<int> resu;
        int i = 0, j = 0;
        while(i+j < n){
            if(s[i+j] == pattern[j]){
                ++j;
                if(j == m){
                    resu.push_back(i);
                }
            }else{
                if(j == 0){
                    ++i;
                }else{
                    i = j+i - table[j];
                    j = table[j];
                }
            }
        }

        return resu;
    }
};