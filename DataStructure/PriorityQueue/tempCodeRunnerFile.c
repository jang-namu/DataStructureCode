

    for (int i=0; i < n-1; i++) {
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        x = make_sub_tree(e1.ptree, e2.ptree);
        e.key = x->key = e1.key + e2.key;
        e.ptree = x;