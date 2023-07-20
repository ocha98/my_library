class KMP {
    private:
    vector<int> table;
    string pattern;

    void create_table(){
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

    string::size_type search(const string& s, int pos = 0) const {
        assert(table.size() > 0);
        const int n = s.length();
        const int m = pattern.length();

        int i = pos, j = 0;
        while(i+j < n){
            if(s[i+j] == pattern[j]){
                ++j;
                if(j == m){
                    return i;
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

        return string::npos;
    }
};

string str_replace(const string& s, const string& from, const string& to){
    string result = s;
    string::size_type pos = 0;

    KMP kmp(from);

    while(true){
        pos = kmp.search(result, pos);
        if(pos == string::npos){
            break;
        }

        result.replace(pos, from.length(), to);
        pos += to.size();
    }

    return result;
}