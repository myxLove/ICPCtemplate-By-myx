//
// Created by leo on 24-8-17.
//

/*
 *using namespace __gun_pbds
 *tree<key,value,function,tree_type(tag),Node_Update,Alloc>
 *tree<键类型，映射的值类型，比较函数，实现方式，节点更新方式，内存分配器>
 *
 *成员函数：
 *1.find            查找权值对应的节点
 *2.insert          插入新节点
 *3.erase           删除迭代器所指向的节点
 *4.lower_bound     第一个大于等于某元素的迭代器
 *5.upper_bound     第一个大于某元素的迭代器
 *6.join            平衡树合并 —— 合并后另一个树会变成空
 *7.split(key,tree) 平衡树分裂，将大于key的元素放进tree里，如果用的是greater则是小于key
 *8.node_begin      根节点的迭代器
 *9.node_end        最后一个叶子节点后的一个空节点的迭代器
 *10.clear          清空容器
 *11.empty          容器是否为空
 *12.size           容器大小
 *
 *(以下需要以 tree_order_statistics_node_update 为更新节点的策略)
 *13.order_of_key   返回x以Cmp_Fn比较的排名
 *14.find_by_order  返回Cmp_Fn比较的排名所对应元素的迭代器
 *
 *提供的平衡树模板(tree_type)有：
 *1.basic_tree_tag          基类——没什么实际用途
 *2.tree_tag                基类——没什么实际用途
 *3.rb_tree_tag             红黑树 —— 性能最优
 *4.splay_tree_tag          splay树
 *5.ov_tree_tag             有序向量树(排序向量)
 *
 *如果无映射，则可以当成set使用，此时 value 为 null_type
 *节点更新策略：
 *1.null_node_update    (默认)
 *2.tree_order_statistics_node_update
 *
 */

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