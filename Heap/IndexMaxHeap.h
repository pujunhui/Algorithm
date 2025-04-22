#ifndef HEAP_INDEXMAXHEAP_H
#define HEAP_INDEXMAXHEAP_H

#include <iostream>
#include <assert.h>

template<typename Item>
class IndexMaxHeap {
private:
    Item* data;     // 最大索引堆中的数据
    int* indexes;   // 最大索引堆中的索引, indexes[x] = i 表示索引i在x的位置
    int* reverse;   // 最大索引堆中的反向索引, reverse[i] = x 表示索引i在x的位置

    int count;//大小
    int capacity;//容量

    // 索引堆中, 数据之间的比较根据data的大小进行比较, 但实际操作的是索引
    void shiftUp(int k) {
        while (k > 0) {
            int p = (k - 1) / 2;  //父节点索引
            if (data[indexes[p]] >= data[indexes[k]]) {
                break;
            }
            std::swap(indexes[p], indexes[k]);
            reverse[indexes[p]] = p;
            reverse[indexes[k]] = k;
            k = p;
        }
    }

    // 索引堆中, 数据之间的比较根据data的大小进行比较, 但实际操作的是索引
    void shiftDown(int k) {
        while (k < count) {
            int j = 2 * k + 1; //从k的左子孩子开始往后shiftDown
            if (j >= count) { //左子节点不存在，表示索引k已经是叶子节点
                break;
            }
            if (j + 1 < count && data[indexes[j + 1]] > data[indexes[j]]) { //判断是否有右孩子，并比较左右孩子的大小
                j++;
            }
            if (data[indexes[k]] >= data[indexes[j]]) {
                break;
            }
            std::swap(indexes[k], indexes[j]);
            reverse[indexes[k]] = k;
            reverse[indexes[j]] = j;
            k = j;
        }
    }

public:
    IndexMaxHeap(int capacity) {
        data = new Item[capacity];
        indexes = new int[capacity];
        reverse = new int[capacity];

        this->capacity = capacity;
        count = 0;

        //将indexes数组和reverse数组全部设置为无效
        std::fill_n(reverse, capacity, -1);
    }

    ~IndexMaxHeap() {
        delete[] data;
        delete[] indexes;
        delete[] reverse;
    }

    int size() const {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }

    //传入的i对用户而言，是从0索引的
    void insert(int i, Item item) {
        assert(count + 1 <= capacity);
        assert(i >= 0 && i < capacity);

        // 再插入一个新元素前,还需要保证索引i所在的位置是没有元素的。
        assert(!contain(i));

        data[i] = item;
        int k = count;
        indexes[k] = i;
        reverse[i] = k;
        count++;

        shiftUp(k);
    }

    // 从最大索引堆中取出堆顶元素, 即索引堆中所存储的最大数据
    Item extractMax() {
        assert(count > 0);

        Item ret = data[indexes[0]]; //取出最大元素的值
        reverse[indexes[0]] = -1; //标志堆顶数据已经被移除
        indexes[0] = indexes[count - 1]; //将堆中最后一个元素索引设置为堆顶索引
        reverse[indexes[0]] = 0;  //
        count--;

        shiftDown(0);
        return ret;
    }

    // 从最大索引堆中取出堆顶元素的索引
    int extractMaxIndex() {
        assert(count > 0);

        int ret = indexes[0]; //取出最大元素的索引
        reverse[indexes[0]] = -1; //标志堆顶数据已经被移除
        indexes[0] = indexes[count - 1]; //将堆中最后一个元素索引设置为堆顶索引
        reverse[indexes[0]] = 0;
        count--;

        shiftDown(0);
        return ret;
    }

    // 获取最大索引堆中的堆顶元素
    Item getMax() const {
        assert(count > 0);
        return data[indexes[0]];
    }

    // 获取最大索引堆中的堆顶元素的索引
    int getMaxIndex() const {
        assert(count > 0);
        return indexes[0];
    }

    // 看索引i所在的位置是否存在元素
    bool contain(int i) const {
        assert(i >= 0 && i < capacity);
        return reverse[i] != -1;
    }

    // 获取最大索引堆中索引为i的元素
    Item getItem(int i) const {
        assert(contain(i));
        return data[i];
    }

    // 将最大索引堆中索引为i的元素修改为newItem
    void change(int i, Item newItem) {
        assert(contain(i));
        data[i] = new Item;

        //找到indexes[j] = i，j表示data[i]在堆的位置
        //之后shiftUp(j)，再shiftDown(j)
//        for(int j = 0; j < count; j++)
//        if(indexes[j] == i){
//            shiftUp(j);
//            shiftDown(j);
//            return;
//        }
        shiftUp(reverse[i]);
        shiftDown(reverse[i]);
        return;
    }
};

#endif // HEAP_INDEXMAXHEAP_H
