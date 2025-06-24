#include "binary_tree.h"
#include "algorithm.h"

namespace hbutds{

    struct HuffmanComparator{
        auto operator()(BinaryTreeNode<double>* a, BinaryTreeNode<double>* b) const -> bool{
            return a->data > b->data;
        }
    };

}


auto hbutds::make_huffman_tree(const vector<double>& data) -> BinaryTreeNode<double>*{
    vector<BinaryTreeNode<double>*> heap;
    for(auto d : data){
        heap.push_back(new BinaryTreeNode<double>(d));
    }
    make_heap(heap, HuffmanComparator());

    while(heap.size() > 1){
        auto left {heap[0]};
        pop_heap(heap, HuffmanComparator());
        heap.erase(heap.end() + (-1));

        auto right {heap[0]};
        pop_heap(heap, HuffmanComparator());
        heap.erase(heap.end() + (-1));

        auto new_node {
            new BinaryTreeNode(
                left->data + right->data,
                left, right
            )
        };
        heap.push_back(new_node);
        push_heap(heap, HuffmanComparator());
    }

    return heap[0];
}