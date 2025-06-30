#include "binary_tree.h"
#include "algorithm.h"

namespace hbutds{

    struct HuffmanComparator{
        auto operator()(
                BinaryTreeNode<double>* a, BinaryTreeNode<double>* b
        ) const -> bool {
            return a->data > b->data;
        }
    };

}


auto hbutds::make_huffman_tree(
        const vector<double>& data
) -> BinaryTreeNode<double>* {

    //使用小根堆作为优先队列
    vector<BinaryTreeNode<double>*> heap;
    for(auto d : data){
        heap.push_back(new BinaryTreeNode<double>(d));
    }
    make_heap(heap, HuffmanComparator());

    while(heap.size() > 1){
        // 依次从优先队列中弹出两个元素作为左右孩子
        auto left {heap[0]}; 
        pop_heap(heap, HuffmanComparator());
        heap.erase(heap.end() + (-1));

        auto right {heap[0]};
        pop_heap(heap, HuffmanComparator());
        heap.erase(heap.end() + (-1));

        // 组成新的二叉树节点
        auto new_node {
            new BinaryTreeNode(
                left->data + right->data,
                left, right
            )
        };
        
        // 将新二叉树节点放入优先队列
        heap.push_back(new_node);
        push_heap(heap, HuffmanComparator());
    }

    return heap[0];
}