#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using OrderTree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// OrderTree::insert(x)
// OrderTree::erase(x)
// OrderTree::order_of_key(x): number of elements strictly less than x
// OrderTree::find_by_order(k): k-th smallest element, 0 indexed

/*
int main () {
    OrderTree<int> t;
    t.insert(1);
    t.insert(4);
    t.insert(-1);
    t.insert(9);

    cout << t.order_of_key(4) << "\n";
    cout << t.order_of_key(10) << "\n";
    cout << *t.find_by_order(1) << "\n\n";

    t.erase(1);
    t.erase(2);

    cout << t.order_of_key(4) << "\n";
    cout << t.order_of_key(10) << "\n";
    cout << *t.find_by_order(1) << "\n";

    return 0;
}
//*/