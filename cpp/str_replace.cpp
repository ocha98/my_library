string str_replace(const string& s, const string& from, const string& to){
    string result = s;
    string::size_type pos = 0;
    while(true){
        pos = result.find(from, pos);
        if(pos == string::npos){
            break;
        }

        result.replace(pos, from.length(), to);
        pos += to.size();
    }

    return result;
}
