// template
int now = 0;// CHECK TYPE
vector<int> ans(q);
auto add = [&](int i){
    // TO DO
};
auto del = [&](int i){
    // TO DO
};

const int width = max<int>(1, n/sqrt(q));
vector<int> p(q);
for(int i = 0;i < q; ++i){
    p[i] = i;
}
sort(p.begin(), p.end(), [&](int i, int j){
    if(l[i]/width == l[j]/width){
        return r[i] < r[j];
    }
    return l[i] < l[j];
});

int li = 0, ri = 0;
for(int i: p){
    int nl = l[i], nr = r[i];
    while(ri < nr){
        add(ri);
        ++ri;
    }
    while(li > nl){
        --li;
        add(li);
    }
    while(ri > nr){
        --ri;
        del(ri);
    }
    while(li < nl){
        del(li);
        ++li;
    }
    ans[i] = now;
}
