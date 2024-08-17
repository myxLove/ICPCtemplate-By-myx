//
// Created by leo on 24-8-17.
//


#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
#define INF 0x7ffffff
#define el '\n'
typedef pair<int, int> PII;
typedef tree<PII, null_type, less<PII>, rb_tree_tag, tree_order_statistics_node_update> Tree;
Tree tr;
int tr_clock;
template<typename T>
int getOrder(T x){
    return tr.order_of_key(x) + 1;
}
template<typename T>
T getValue(int k){
    auto it = tr.find_by_order(k - 1);
    if(it != tr.end())
        return *it;
    return {INF, 0};
}
int main(){
    int n;cin >> n;
    int op, x;
    while (n--){
        cin >> op >> x;
        ++ tr_clock;
        switch (op){
            case 1: {
                tr.insert({x, tr_clock});
                break;
            }
            case 2:{
                auto it = tr.upper_bound({x, 0});
                tr.erase(it);
                break;
            }
            case 3:{
                int k = getOrder<PII>({x, 0});
                cout << k << el;
                break;
            }
            case 4:{
                auto v = getValue<PII>(x);
                cout << v.first << el;
                break;
            }
            case 5:{
                auto it = tr.upper_bound({x, 0});
                -- it;
                auto v = *it;
                cout << v.first << el;
                break;
            }
            case 6:{
                auto v = *tr.upper_bound({x, INF});
                cout << v.first << el;
                break;
            }
        }
    }
}