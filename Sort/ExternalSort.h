#pragma once

// 外部排序

// 置换选择排序：
// 最佳归并树：哈夫曼树
// 败者树

template <typename T>
class HuffmanTree {
   private:
    typedef struct Node {
        void *lNext, *rNext;
        int lTag, rTag;
    } Node;

   public:
    HuffmanTree(int *lists[], int n) {
    }
};

template <typename T>
class LoserTree {
   public:
    LoserTree(int capture) {}
    ~LoserTree() {}
};

template <typename T>
void externalSort(T arr[], int n) {}
