#pragma once

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
